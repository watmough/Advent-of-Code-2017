// Advent of Code 2017
// Day 20 - Particle Swarm

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;


typedef struct particle {
    int num;
    vector<int64_t> pos{0,0,0};
    int64_t vel[3];
    int64_t acc[3];
} particle;

int read_particles(vector<particle>& state)
{
    int64_t x,y,z,vx,vy,vz,ax,ay,az;
    int num = 0;
    while (cin >> x >> y >> z >> vx >> vy >> vz >> ax >> ay >> az) {
        particle p;
        p.num = num++;      // particles are 0 - num-1
        p.pos[0] = x;  p.pos[1] = y;  p.pos[2] = z; 
        p.vel[0] = vx; p.vel[1] = vy; p.vel[2] = vz; 
        p.acc[0] = ax; p.acc[1] = ay; p.acc[2] = az; 
        state.push_back(p);
    }
    return num;
}

void step(particle& p)
{
    p.vel[0] += p.acc[0]; p.vel[1] += p.acc[1]; p.vel[2] += p.acc[2]; 
    p.pos[0] += p.vel[0]; p.pos[1] += p.vel[1]; p.pos[2] += p.vel[2]; 
}

int main()
{
    // read in particles
    vector<particle> state;
    int num_particles = read_particles(state);
    // loop
    int ucount = state.size();
    int generations = 0;
    while (1)
    {
        // sort by position and eliminate dupes
        map<vector<int64_t>,int> dupes;
        for (auto it=begin(state);it!=end(state);++it) {
            dupes[((*it).pos)]++;
        }

        // filter dupes so only includes collision locations
        for (auto it=begin(dupes);it!=end(dupes);) {
            if ((*it).second>1) {
                cout << "dupe at pos " << (*it).first[0] << "," << (*it).first[1] << "," << (*it).first[2] << endl;
                it++;
            } else {
                it = dupes.erase(it++);
            }
        }

        // remove collided particles
        state.erase(remove_if(begin(state),end(state),[&](particle p)->bool{if (dupes.find(p.pos)!=end(dupes)) return true; else return false;}),end(state));
        cout << "Duplicates: " << dupes.size() << " particles: " << state.size() << " gen: " << generations++ << endl;

        // step time
        for (auto it=begin(state);it!=end(state);++it) {
            step(*it);
        }
    }
}
