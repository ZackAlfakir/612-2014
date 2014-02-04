#include "UpdateRegistry.h"

UpdateRegistry::UpdateRegistry() {
    
}

UpdateRegistry::~UpdateRegistry() {
    
}

void UpdateRegistry::add(obj o, helper h) {
    registry_object r;
    r.o = o;
    r.h = h;
    registry.push_back(r);
}

void UpdateRegistry::update() {
    for (int i = 0; i < (int)registry.size(); i++) {
        ((registry.at(i)).h)((registry.at(i)).o);
    }
}
