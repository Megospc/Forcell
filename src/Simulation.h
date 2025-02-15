// Simulation class

#pragma once

#include "Definitions.h"
#include "Random.h"

#define MAX_SIMULATION_THREADS 256
#define MAX_REACTIONS 100

#include <thread>

namespace Simulation {
    struct Rule {
        float friction = 0.01;
        float attractor = 0.00025;
        float bounceForce = 0.5;
        float massSpread = 0.0;

        int types = 2;

        int forcetype = 0;
        // 0 = Forcell
        // 1 = Constant
        // 2 = Classic

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

        bool connections = false;

        float connectionNormal = 30.0;
        float connectionDistance = 50.0;
        float connectionAttraction = 0.01;
        float connectionReplusion = 0.0;
        float connectionMax = 100.0;

        int connectionsPriority[100];

        bool reactions = false;

        float reactionDistance = 100.0;

        int reactionsTable[5*MAX_REACTIONS];

        int reactionsCount = 0;

        void random(uint seed, float forcerange, float zonerange) {
            Rand::Seed(seed);

            for (uint i = 0; i < 10; i++) freqs[i] = Rand::Range(0.01, 1.00);

            for (uint i = 0; i < 100; i++) {
                float f = Rand::Range(0.0, forcerange);

                forces[i] = Rand::Sign()*f;

                float r = Rand::Range(0.0, SQRT(zonerange));

                zones[i] = r*r;

                float f2 = Rand::Range(0.0, forcerange);

                forces2[i] = Rand::Sign()*f2-forces[i];

                float r2 = Rand::Range(0.0, SQRT(zonerange));

                zones2[i] = r2*r2;
            }

            friction = Rand::Range(0.001, 0.100);
            attractor = 0.0;
            bounceForce = Rand::Range(0.1, 0.4);

            for (uint i = 0; i < 100; i++) {
                uint slot = (i/2)%5;

                connectionsPriority[i] = Rand::Chance(0.75-(float)slot/5.0*0.6) ? Rand::Int(types):-1;
            }

            connectionNormal = Rand::Range(30.0, 100.0);
            connectionDistance = connectionNormal+Rand::Range(30.0, 100.0);
            connectionMax = connectionDistance+Rand::Range(30.0, 100.0);
            connectionAttraction = 0.01;
            connectionReplusion = 0.0;

            reactionDistance = Rand::Range(50.0, 200.0);
            reactionsCount = Rand::Int(6);

            for (uint i = 0; i < reactionsCount; i++) {
                reactionsTable[i*5] = Rand::Int(types);
                reactionsTable[i*5+1] = Rand::Int(types);
                reactionsTable[i*5+2] = Rand::Int(types);
                reactionsTable[i*5+3] = Rand::Chance(0.5) ? Rand::Int(types):-1;
                reactionsTable[i*5+4] = Rand::Chance(0.1) ? Rand::Int(types):-1;
            }
        }

        // Metadata
        char name[256] = { 'U', 'n', 'n', 'a', 'm', 'e', 'd', '\0' };
        char creator[256] = { '\0' };
        char lastupdate[256] = { '[', 'n', 'o', 't', ' ', 'p', 'r', 'o', 'v', 'i', 'd', 'e', 'd', ']', '\0' };
    };

    struct Params {
        int width = 1000;
        int height = 1000;

        uint seed = 1;

        int particles = 400;

        float initialForce = 0.0;

        Rule* rule;
    };

    struct Particle {
        float x, y;
        float vx, vy;
        float size;
        float mass;
        int type;
        int ntype;
        int connections[5];
        int connis[5]; // Connection IDs
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

    #define TASKFN_EXTDEFINER(name) \
        void task1forcell##name(uint, uint); \
        void task2forcell##name(uint, uint); \
        void task1classic##name(uint, uint); \
        void task2classic##name(uint, uint); \
        void task1const##name(uint, uint); \
        void task2const##name(uint, uint);

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

                float mspread = rule->massSpread+1.0;

                for (uint i = 0; i < particlesCount; i++) {
                    particles[i].x = Rand::Range(0.0, width);
                    particles[i].y = Rand::Range(0.0, height);

                    particles[i].size = Rand::Range(10.0/mspread, 10.0*mspread);
                    particles[i].type = GetParticleType(rule, (float)i/(particlesCount-1)*sumfreq);
                    particles[i].ntype = -1;

                    for (uint j = 0; j < 5; j++) particles[i].connections[j] = -1;

                    float mass = particles[i].size*particles[i].size/100.0;

                    particles[i].mass = mass;

                    particles[i].vx = Rand::Range(-params.initialForce, params.initialForce)/mass;
                    particles[i].vy = Rand::Range(-params.initialForce, params.initialForce)/mass;
                }

                frame = 0;
            }

            ~Simulation() {
                free(particles);
            }

            void shove(float x, float y, float r, float force) {
                float r2 = r*r;

                for (uint i = 0; i < particlesCount; i++) {
                    Particle* a = &particles[i];

                    float dx = x-a->x;
                    float dy = y-a->y;

                    float d2 = dx*dx+dy*dy;

                    if (d2 > r2) continue;

                    if (d2 < 1.0) dx = 1.0, d2 = 1.0, dy = 0.0;

                    float f = -force/d2;

                    a->vx += dx*f;
                    a->vy += dy*f;
                }
            }

            void slowdown(float x, float y, float r, float friction) {
                float r2 = r*r;

                for (uint i = 0; i < particlesCount; i++) {
                    Particle* a = &particles[i];

                    float dx = x-a->x;
                    float dy = y-a->y;

                    float d2 = dx*dx+dy*dy;

                    if (d2 > r2) continue;

                    a->vx *= 1.0-friction;
                    a->vy *= 1.0-friction;
                }
            }

            void moveit(float fx, float fy, float x, float y, float r, float force, float friction) {
                float r2 = r*r;

                fx *= force, fy *= force;

                for (uint i = 0; i < particlesCount; i++) {
                    Particle* a = &particles[i];

                    float dx = x-a->x;
                    float dy = y-a->y;

                    float d2 = dx*dx+dy*dy;

                    if (d2 > r2) continue;

                    a->vx *= 1.0-friction;
                    a->vy *= 1.0-friction;

                    a->vx += fx;
                    a->vy += fy;
                }
            }

           TASKFN_EXTDEFINER();
           TASKFN_EXTDEFINER(_connections);
           TASKFN_EXTDEFINER(_reactions);
           TASKFN_EXTDEFINER(_connections_reactions);

            void step(uint, float);

            float width, height;

            Particle* particles;

            uint particlesCount;

            Rule* rule;

            uint frame;

        private:
            bool isConnected(uint a, uint b) {
                int* connections = particles[a].connections;

                return connections[0] == b ||
                    connections[1] == b ||
                    connections[2] == b ||
                    connections[3] == b ||
                    connections[4] == b;
            }

            int connectionPriority(uint atype, uint btype, uint i) {
                int* p = &rule->connectionsPriority[atype*10+i*2];

                if (p[1] == btype) return 1;
                if (p[0] == btype) return 2;

                return 0;
            }

            int canConnect(uint a, uint b) {
                Particle* pa = &particles[a];
                Particle* pb = &particles[b];
                
                for (uint i = 0; i < 5; i++) {
                    uint c = pa->connections[i];

                    uint pnew = connectionPriority(pa->type, pb->type, i);
                    uint pcur = c == -1 ? 0:
                        connectionPriority(pa->type, particles[c].type, i);

                    if (pnew > pcur) return i;
                }

                return -1;
            }

            void killConnect(uint a, uint i) {
                Particle* p = &particles[a];

                if (p->connections[i] == -1) return;
                
                particles[p->connections[i]].connections[p->connis[i]] = -1;
                particles[a].connections[i] = -1;
            }

            void tryConnect(uint a, uint b) {
                int acan = canConnect(a, b);

                if (acan == -1) return;

                int bcan = canConnect(b, a);

                if (bcan == -1) return;

                killConnect(a, acan);
                killConnect(b, bcan);

                particles[a].connections[acan] = b;
                particles[a].connis[acan] = bcan;
                particles[b].connections[bcan] = a;
                particles[b].connis[bcan] = acan;
            } 
    };

    // Some very complex manipulations with #define to create to create many variants of one function easier.

    // Function declaration
    #define SIMULATION_TASKFN(name, code) void Simulation::name(uint start, uint end) { \
        code \
    } 

    // Main loops
    #define TASKFN_LOOP1(code) for (uint i = start; i < end; i++) { \
        Particle* a = &particles[i]; \
        \
        code \
    }
    #define TASKFN_LOOP2(code) for (uint j = 0; j < particlesCount; j++) { \
        if (i == j) continue; \
        \
        Particle* b = &particles[j]; \
        \
        code \
    }

    // Calculate distance
    #define TASKFN_DISTANCE \
        float dx = b->x-a->x; \
        float dy = b->y-a->y; \
        \
        float d2 = dx*dx+dy*dy;
    
    // Calculate minimal distance
    #define TASKFN_RADIUSES \
        float rr = a->size+b->size; \
        float rr2 = rr*rr;
    
    // Accept force to particle
    #define TASKFN_ACCEPTFORCE \
        a->vx += dx*f; \
        a->vy += dy*f;
    
    // Check if minimum distance has been reached
    #define TASKFN_MINDIST if (d2 < 0.0001) dx = 1.0, d2 = 1.0, dy = 0.0;

    // Collision test
    #define TASKFN_COLLITEST (d2 < rr2 && rule->bounceForce > 0.0) || d2 < 0.0001

    // Ca;culate collision force
    #define TASKFN_COLLIFORCE \
        float d = SQRT(d2); \
        \
        float depth = rr-d; \
        \
        f = -depth/d*rule->bounceForce*a->mass*b->mass/(a->mass+b->mass);
    
    #define TASKFN_RULEIDX uint ruleidx = a->type*10+b->type;

    #define TASKFN_FORCE \
        float maxd = rule->zones[ruleidx]; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 > maxd2) continue; \
        \
        f = rule->forces[ruleidx]/d2;
    
    #define TASKFN_FORCEADD(zones, forces) { \
        float maxd = rule->zones[ruleidx]; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 <= maxd2) f += rule->forces[ruleidx]/d2; \
    }

    #define TASKFN_CONST_FORCE \
        float maxd = rule->zones[ruleidx]; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 > maxd2) continue; \
        \
        float d = SQRT(d2); \
        \
        f = rule->forces[ruleidx]/d*0.1;
    
    #define TASKFN_CONST_FORCEADD(zones, forces) { \
        float maxd = rule->zones[ruleidx]; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 <= maxd2) { \
            float d = SQRT(d2); \
            \
            f += rule->forces[ruleidx]/d*0.1; \
        } \
    }

    #define TASKFN_CLASSIC_FORCE \
        float zd = rule->zones[ruleidx]; \
        float maxd = zd*2+rr; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 > maxd2) continue; \
        \
        float d = SQRT(d2); \
        float dz = (d-rr)/zd; \
        \
        if (d < 1.0) f = rule->forces[ruleidx]*dz/d*0.003; \
        else f = rule->forces[ruleidx]*(2.0-dz)/d*0.003;
    
    #define TASKFN_CLASSIC_FORCEADD(zones, forces) { \
        float zd = rule->zones[ruleidx]; \
        float maxd = zd*2+rr; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 <= maxd2) { \
            float d = SQRT(d2); \
            float dz = (d-rr)/zd; \
            \
            if (d < 1.0) f = rule->forces[ruleidx]*dz/d*0.003; \
            else f = rule->forces[ruleidx]*(2.0-dz)/d*0.003; \
        } \
    }

    #define TASKFN_FORCELL(name, code, ext, ext1, ext2) SIMULATION_TASKFN(name, \
        TASKFN_LOOP1( \
            ext1 \
            TASKFN_LOOP2( \
                TASKFN_DISTANCE \
                TASKFN_RADIUSES \
                \
                float f = 0.0; \
                \
                ext \
                \
                if (TASKFN_COLLITEST) { \
                    TASKFN_MINDIST \
                    TASKFN_COLLIFORCE \
                } else { \
                    TASKFN_RULEIDX \
                    \
                    code \
                } \
                \
                TASKFN_ACCEPTFORCE \
            ) \
            ext2 \
        ) \
    )

    #define TASKFN_CONSTANT(name, code, ext, ext1, ext2) SIMULATION_TASKFN(name, \
        TASKFN_LOOP1( \
            ext1 \
            TASKFN_LOOP2( \
                TASKFN_DISTANCE \
                \
                float f = 0.0; \
                \
                ext \
                \
                TASKFN_RULEIDX \
                \
                TASKFN_MINDIST \
                \
                code \
                \
                TASKFN_ACCEPTFORCE \
            ) \
            ext2 \
        ) \
    )

    #define TASKFN_CLASSIC(name, code, ext, ext1, ext2) SIMULATION_TASKFN(name, \
        TASKFN_LOOP1( \
            ext1 \
            TASKFN_LOOP2( \
                TASKFN_DISTANCE \
                TASKFN_RADIUSES \
                \
                float f = 0.0; \
                \
                ext \
                \
                if ((d2 < rr2) || d2 < 0.0001) { \
                    TASKFN_MINDIST \
                    \
                    float d = SQRT(d2); \
                    \
                    float depth = (rr-d)/rr; \
                    \
                    f = -depth*rule->bounceForce/d; \
                } else { \
                    TASKFN_RULEIDX \
                    \
                    code \
                } \
                TASKFN_ACCEPTFORCE \
            ) \
            ext2 \
        ) \
    )

    #define TASK1_FORCELL(name, ext, ext1, ext2) TASKFN_FORCELL(task1forcell##name, TASKFN_FORCE, ext, ext1, ext2)
    #define TASK2_FORCELL(name, ext, ext1, ext2) TASKFN_FORCELL(task2forcell##name, TASKFN_FORCEADD(zones, forces) TASKFN_FORCEADD(zones2, forces2), ext, ext1, ext2)
    #define TASK1_CONST(name, ext, ext1, ext2) TASKFN_CONSTANT(task1const##name, TASKFN_CONST_FORCE, ext, ext1, ext2)
    #define TASK2_CONST(name, ext, ext1, ext2) TASKFN_CONSTANT(task2const##name, TASKFN_CONST_FORCEADD(zones, forces) TASKFN_CONST_FORCEADD(zones2, forces2), ext, ext1, ext2)
    #define TASK1_CLASSIC(name, ext, ext1, ext2) TASKFN_CLASSIC(task1classic##name, TASKFN_CLASSIC_FORCE, ext, ext1, ext2)
    #define TASK2_CLASSIC(name, ext, ext1, ext2) TASKFN_CLASSIC(task2classic##name, TASKFN_CLASSIC_FORCEADD(zones, forces) TASKFN_CLASSIC_FORCEADD(zones2, forces2), ext, ext1, ext2)

    #define TASKFN_EXTENSER(name, ext, ext1, ext2) \
        TASK1_FORCELL(name, ext, ext1, ext2); \
        TASK2_FORCELL(name, ext, ext1, ext2); \
        TASK1_CONST(name, ext, ext1, ext2); \
        TASK2_CONST(name, ext, ext1, ext2); \
        TASK1_CLASSIC(name, ext, ext1, ext2); \
        TASK2_CLASSIC(name, ext, ext1, ext2);
    
    #define TASKFN_EXT_CONNECTIONS { \
        float maxd = rule->connectionDistance; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 < maxd2 && !isConnected(i, j)) { \
            tryConnect(i, j); \
        } \
    }

    #define TASKFN_EXT_REACTIONS { \
        float maxd = rule->reactionDistance; \
        float maxd2 = maxd*maxd; \
        \
        if (d2 < maxd2) { \
            for (uint k = 0; k < rule->reactionsCount; k++) { \
                for (uint l = 0; l < 3; l++) { \
                    if (rule->reactionsTable[k*3+2+l] == b->type && !reactions[k*3+l]) { \
                        reactions[k*3+l] = true; \
                        break; \
                    } \
                } \
            } \
        } \
    }

    #define TASKFN_EXT1_REACTIONS \
        bool reactions[MAX_REACTIONS*3]; \
        \
        for (uint i = 0; i < rule->reactionsCount; i++) { \
            for (uint j = 0; j < 3; j++) { \
                reactions[i*3+j] = rule->reactionsTable[i*5+2+j] == -1 ? true:false; \
            } \
        }
    
    #define TASKFN_EXT2_REACTIONS \
        for (uint i = 0; i < rule->reactionsCount; i++) { \
            if (rule->reactionsTable[i*5] != a->type) continue; \
            \
            if (reactions[i*3] && reactions[i*3+1] && reactions[i*3+2]) a->ntype = rule->reactionsTable[i*5+1]; \
        }

    #define TASKFN_EXTUSER(name) \
        if (self->rule->secondtable) { \
            if (self->rule->forcetype == 0) self->task2forcell##name(start, end); \
            if (self->rule->forcetype == 1) self->task2const##name(start, end); \
            if (self->rule->forcetype == 2) self->task2classic##name(start, end); \
        } else { \
            if (self->rule->forcetype == 0) self->task1forcell##name(start, end); \
            if (self->rule->forcetype == 1) self->task1const##name(start, end); \
            if (self->rule->forcetype == 2) self->task1classic##name(start, end); \
        }
    
    TASKFN_EXTENSER(,,,); // No extensions
    TASKFN_EXTENSER(_connections, TASKFN_EXT_CONNECTIONS,,); // Connections
    TASKFN_EXTENSER(_reactions, TASKFN_EXT_REACTIONS, TASKFN_EXT1_REACTIONS, TASKFN_EXT2_REACTIONS); // Reactions
    TASKFN_EXTENSER(_connections_reactions, TASKFN_EXT_CONNECTIONS TASKFN_EXT_REACTIONS, TASKFN_EXT1_REACTIONS, TASKFN_EXT2_REACTIONS); // Reactions + Connections

    void task(Simulation* self, uint start, uint end) {
        if (self->rule->connections) {
            if (self->rule->reactions) {
                TASKFN_EXTUSER(_connections_reactions);
            } else {
                TASKFN_EXTUSER(_connections);
            }
        } else {
            if (self->rule->reactions) {
                TASKFN_EXTUSER(_reactions);
            } else {
                TASKFN_EXTUSER();
            }
        }
    }

    void Simulation::step(uint threadcount, float speedup) {
        std::thread* threads[MAX_SIMULATION_THREADS];

        float curstart = 0.0;
        float sumtask = particlesCount;
        float perthread = sumtask/threadcount;

        #ifndef NDEBUG
        Logger::Bench::Start();
        #endif

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
        
        #ifndef NDEBUG
        Log("Main process: " << Logger::Bench::End() << "ms");

        Logger::Bench::Start();
        #endif

        for (uint i = 0; i < particlesCount; i++) {
            Particle* a = &particles[i];

            if (rule->connections) for (uint j = 0; j < 5; j++) {
                uint bi = a->connections[j];

                if (bi == -1) continue;

                Particle* b = &particles[bi];

                float dx = b->x-a->x;
                float dy = b->y-a->y;

                float d = SQRT(dx*dx+dy*dy);

                if (d < 0.001) dx = 1.0, dy = 0.0, d = 1.0;

                if (d >= rule->connectionMax) killConnect(i, j);

                float f = d-rule->connectionNormal;

                if (d > rule->connectionNormal) f *= rule->connectionAttraction;
                else f *= rule->connectionReplusion;

                a->vx += dx*f/d;
                a->vy += dy*f/d;
            }

            a->x += a->vx*speedup/a->mass;
            a->y += a->vy*speedup/a->mass;

            a->vx -= (a->x-width/2.0)*rule->attractor*speedup;
            a->vy -= (a->y-height/2.0)*rule->attractor*speedup;

            a->vx *= 1.0-rule->friction;
            a->vy *= 1.0-rule->friction;

            if (a->x < a->size) a->x = a->size, a->vx = ABS(a->vx);
            if (a->y < a->size) a->y = a->size, a->vy = ABS(a->vy);
            if (a->x >= width-a->size) a->x = width-a->size, a->vx = IABS(a->vx);
            if (a->y >= height-a->size) a->y = height-a->size, a->vy = IABS(a->vy);

            if (a->ntype >= 0) a->type = a->ntype, a->ntype = -1;
        }

        #ifndef NDEBUG
        Log("After-forces process: " << Logger::Bench::End() << "ms");
        #endif

        frame++;
    }

    uint GetThreads() {
        return std::thread::hardware_concurrency();
    }
}