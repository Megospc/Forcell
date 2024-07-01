// Simulation class

#pragma once

#include "Definitions.h"
#include "Random.h"

#ifdef SIMULATION_THREADS
#include <thread>
#endif

namespace Simulation {
    struct Rule {
        float friction = 0.001;
        float attractor = 0.0;

        int types = 2;

        float forces[100];

        float freqs[10] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

        void clamp() {
            SCLAMP(friction, 0.0, 1.0);
            SCLAMP(attractor, 0.0, 0.1);
            SCLAMP(types, 1, 10);
        }

        void random() {

        }
    };

    struct Params {
        int width = 1000;
        int height = 1000;

        int seed = 1;

        int particles = 400;

        Rule* rule;

        void clamp() {
            
        }
    };

    struct Particle {
        float x, y;
        float vx, vy;
        float size;
        int type;
    };

    int GetParticleType(Rule* rule, float v) {
        float cur = 0.0;

        for (uint i = 0; i < rule->types; i++) {
            float freq = rule->freqs[i];

            if (v >= cur && v <= cur+freq) return i;
            
            cur += freq;
        }

        return 0;
    }

    class Simulation {
        public:
            Simulation(Params params) {
                this->rule = params.rule;

                width = params.width;
                height = params.height;

                particlesCount = params.particles;

                particles = MALLOC(Particle, particlesCount);

                float sumfreq = 0.0;
                for (uint i = 0; i < rule->types; i++) sumfreq += rule->freqs[i];

                Rand::Seed(params.seed);

                for (uint i = 0; i < particlesCount; i++) {
                    particles[i].x = Rand::Range(0.0, width);
                    particles[i].y = Rand::Range(0.0, height);

                    particles[i].vx = 0.0;
                    particles[i].vy = 0.0;

                    particles[i].size = 10.0;
                    particles[i].type = GetParticleType(rule, Rand::Range(0.0, sumfreq));
                }

                frame = 0;
            }

            ~Simulation() {
                free(particles);
            }

            void _task(uint, uint);
            void step();

            float width, height;

            Particle* particles;

            uint particlesCount;

            Rule* rule;

            uint frame;
            
    };

    void task(Simulation* self, uint start, uint end) {
        self->_task(start, end);
    }

    void Simulation::_task(uint start, uint end) {
        for (uint i = start; i < end; i++) {
            Particle* a = &particles[i];

            for (uint j = 0; j < particlesCount; j++) {
                if (i == j) continue;

                Particle* b = &particles[j];

                float dx = b->x-a->x;
                float dy = b->y-a->y;

                float d2 = dx*dx+dy*dy;

                float rr = a->size+b->size;
                float rr2 = rr*rr;

                float f; // Force

                if (d2 < rr2) { // Collision
                    float d = SQRT(d2);

                    float depth = rr-d;

                    f = -depth/2.0/d;
                } else {
                    f = rule->forces[a->type*10+b->type]/d2;
                }

                a->vx += dx*f;
                a->vy += dy*f;
            }
        }
    }

    void Simulation::step() {
        #ifdef SIMULATION_THREADS
        std::thread* threads[SIMULATION_THREADS];

        float curstart = 0.0;
        float sumtask = particlesCount;
        float perthread = sumtask/SIMULATION_THREADS;

        for (uint i = 0; i < SIMULATION_THREADS; i++) {
            threads[i] = new std::thread(
                task,
                this,
                curstart,
                i == SIMULATION_THREADS-1 ? particlesCount:curstart+perthread
            );

            curstart += perthread;
        }

        for (uint i = 0; i < SIMULATION_THREADS; i++) threads[i]->join();

        for (uint i = 0; i < SIMULATION_THREADS; i++) delete threads[i];
        #else
        _task(0, particlesCount);
        #endif

        for (uint i = 0; i < particlesCount; i++) {
            Particle* a = &particles[i];

            a->x += a->vx;
            a->y += a->vy;

            a->vx -= (a->x-width/2.0)*rule->attractor;
            a->vy -= (a->y-height/2.0)*rule->attractor;

            a->vx *= 1.0-rule->friction;
            a->vy *= 1.0-rule->friction;

            if (a->x < a->size) a->x = a->size, a->vx = ABS(a->vx);
            if (a->y < a->size) a->y = a->size, a->vy = ABS(a->vy);
            if (a->x >= width-a->size) a->x = width-a->size, a->vx = IABS(a->vx);
            if (a->y >= height-a->size) a->y = height-a->size, a->vy = IABS(a->vy);
        }

        frame++;
    }
}