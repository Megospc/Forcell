// Simulation class

#pragma once

#include "Definitions.h"
#include "Random.h"

#define MAX_SIMULATION_THREADS 256

#include <thread>

namespace Simulation {
    struct Rule {
        float friction = 0.01;
        float attractor = 0.00025;
        float bounceForce = 0.5;

        int types = 2;

        float forces[100] = {
            0.1 , 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            -0.1, 0.08, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0 , 0.0 , 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
        };

        float zones[100] = {
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
            1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0, 1000.0,
        };

        float freqs[10] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

        void clamp() {
            SCLAMP(types, 1, 10);
        }

        void random(uint seed) {
            Rand::Seed(seed);

            for (uint i = 0; i < 10; i++) freqs[i] = Rand::Range(0.01, 1.00);

            for (uint i = 0; i < 100; i++) {
                float f = Rand::Range(0.0, 1.0);

                forces[i] = Rand::Sign()*f*f;

                float r = Rand::Range(0.0, 1000.0*1000.0);

                zones[i] = Rand::Sign()*r*r;
            }

            friction = Rand::Range(0.001, 0.100);
            attractor = 0.0;
            bounceForce = Rand::Range(0.5, 1.0);
        }
    };

    struct Params {
        int width = 1000;
        int height = 1000;

        uint seed = 1;

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
            void step(uint);

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

                if ((d2 < rr2 && rule->bounceForce > 0.0) || d2 < 0.0001) { // Collision
                    float d = SQRT(d2);

                    float depth = rr-d;

                    f = -depth/2.0/d*rule->bounceForce;
                } else {
                    uint ruleidx = a->type*10+b->type;

                    float maxd = rule->zones[ruleidx];
                    float maxd2 = maxd*maxd;

                    if (d2 > maxd2) continue;

                    f = rule->forces[ruleidx]/d2;
                }

                a->vx += dx*f;
                a->vy += dy*f;
            }
        }
    }

    void Simulation::step(uint threadcount) {
        std::thread* threads[MAX_SIMULATION_THREADS];

        float curstart = 0.0;
        float sumtask = particlesCount;
        float perthread = sumtask/threadcount;

        for (uint i = 0; i < threadcount; i++) {
            threads[i] = new std::thread(
                task,
                this,
                curstart,
                i == threadcount-1 ? particlesCount:curstart+perthread
            );

            curstart += perthread;
        }

        for (uint i = 0; i < threadcount; i++) threads[i]->join();

        for (uint i = 0; i < threadcount; i++) delete threads[i];

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

    uint GetThreads() {
        return std::thread::hardware_concurrency();
    }
}