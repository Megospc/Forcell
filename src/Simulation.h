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

        bool secondtable = false;

        float forces2[100] = {
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
            0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
        };

        float zones2[100] = {
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
                float f = Rand::Range(0.0, 3.0);

                forces[i] = Rand::Sign()*f*f;

                float r = Rand::Range(0.0, SQRT(1000.0));

                zones[i] = r*r;

                float f2 = Rand::Range(0.0, 3.0);

                forces2[i] = Rand::Sign()*f2*f2-forces[i];

                float r2 = Rand::Range(0.0, SQRT(1000.0));

                zones2[i] = r2*r2;
            }

            friction = Rand::Range(0.001, 0.100);
            attractor = 0.0;
            bounceForce = Rand::Range(0.1, 0.4);
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

            void task1table(uint, uint);
            void task2table(uint, uint);
            void step(uint, float);

            float width, height;

            Particle* particles;

            uint particlesCount;

            Rule* rule;

            uint frame;
            
    };

    void task(Simulation* self, uint start, uint end) {
        if (self->rule->secondtable) self->task2table(start, end);
        else self->task1table(start, end);
    }

    // Some very complex manipulations with #define to create to create many variants of one function easier.

    // Function declaration
    #define SIMULATION_TASKFN(name, code) void Simulation::name(uint start, uint end) { \
        code \
    } 

    // Main loops
    #define SIMULATION_TASKFN_LOOPS(code) for (uint i = start; i < end; i++) { \
        Particle* a = &particles[i]; \
        \
        for (uint j = 0; j < particlesCount; j++) { \
            if (i == j) continue; \
            \
            Particle* b = &particles[j]; \
            \
            code \
        } \
    }

    // Calculate distance
    #define SIMULATION_TASKFN_DISTANCE \
        float dx = b->x-a->x; \
        float dy = b->y-a->y; \
        \
        float d2 = dx*dx+dy*dy;
    
    // Calculate minimal distance
    #define SIMULATION_TASKFN_RADIUSES \
        float rr = a->size+b->size; \
        float rr2 = rr*rr;
    
    // Accept force to particle
    #define SIMULATION_TASKFN_ACCEPTFORCE \
        a->vx += dx*f; \
        a->vy += dy*f;
    
    // Check if minimum distance has been reached
    #define SIMULATION_TASKFN_MINDIST if (d2 < 0.0001) dx = 1.0, d2 = 1.0, dy = 0.0;

    // Collision test
    #define SIMULATION_TASKFN_COLLITEST (d2 < rr2 && rule->bounceForce > 0.0) || d2 < 0.0001

    // Ca;culate collision force
    #define SIMULATION_TASKFN_COLLIFORCE \
        float d = SQRT(d2); \
        \
        float depth = rr-d; \
        \
        f = -depth/2.0/d*rule->bounceForce;
    
    #define SIMULATION_TASKFN_RULEIDX uint ruleidx = a->type*10+b->type;

    #define SIMULATION_TASKFN_FORCE \
        float maxd = rule->zones[ruleidx]; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 > maxd2) continue; \
        \
        f = rule->forces[ruleidx]/d2;
    
    #define SIMULATION_TASKFN_FORCEADD(zones, forces) { \
        float maxd = rule->zones[ruleidx]; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 <= maxd2) f += rule->forces[ruleidx]/d2; \
    }

    SIMULATION_TASKFN(task1table, // One table, no extensions
        SIMULATION_TASKFN_LOOPS(
            SIMULATION_TASKFN_DISTANCE
            SIMULATION_TASKFN_RADIUSES
            float f;

            if (SIMULATION_TASKFN_COLLITEST) {
                SIMULATION_TASKFN_MINDIST
                SIMULATION_TASKFN_COLLIFORCE
            } else {
                SIMULATION_TASKFN_RULEIDX

                SIMULATION_TASKFN_FORCE
            }

            SIMULATION_TASKFN_ACCEPTFORCE
        )
    )

    SIMULATION_TASKFN(task2table, // Two tables, no extensions
        SIMULATION_TASKFN_LOOPS(
            SIMULATION_TASKFN_DISTANCE
            SIMULATION_TASKFN_RADIUSES
            float f = 0.0;

            if (SIMULATION_TASKFN_COLLITEST) {
                SIMULATION_TASKFN_MINDIST
                SIMULATION_TASKFN_COLLIFORCE
            } else {
                SIMULATION_TASKFN_RULEIDX

                SIMULATION_TASKFN_FORCEADD(zones, forces)
                SIMULATION_TASKFN_FORCEADD(zones2, forces2)
            }

            SIMULATION_TASKFN_ACCEPTFORCE
        )
    )

    /*void Simulation::task1table(uint start, uint end) {
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
                    float d;

                    if (d2 < 0.001) dx = 1.0, d2 = 1.0, d = 1.0, dy = 0.0;
                    else d = SQRT(d2);

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

    void Simulation::task2table(uint start, uint end) {
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

                    if (d < 0.01) dx = 1.0, d = 1.0, dy = 0.0;

                    float depth = rr-d;

                    f = -depth/2.0/d*rule->bounceForce;
                } else {
                    uint ruleidx = a->type*10+b->type;

                    f = 0.0;

                    float max1d = rule->zones[ruleidx];
                    float max1d2 = max1d*max1d;

                    if (d2 <= max1d2) f += rule->forces[ruleidx]/d2;

                    float max2d = rule->zones2[ruleidx];
                    float max2d2 = max2d*max2d;

                    if (d2 <= max2d2) f += rule->forces2[ruleidx]/d2;
                }

                a->vx += dx*f;
                a->vy += dy*f;
            }
        }
    }*/

    void Simulation::step(uint threadcount, float speedup) {
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

            a->x += a->vx*speedup;
            a->y += a->vy*speedup;

            a->vx -= (a->x-width/2.0)*rule->attractor*speedup;
            a->vy -= (a->y-height/2.0)*rule->attractor*speedup;

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