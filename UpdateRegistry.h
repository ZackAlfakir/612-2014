#ifndef UPDATE_REGISTRY
#define UPDATE_REGISTRY

#include <vector>

typedef void* obj;
typedef void(*helper)(obj);

struct registry_object {
    obj o;
    helper h;
};

class UpdateRegistry {
public:
    UpdateRegistry();
    ~UpdateRegistry();
    void add(obj, helper);
    void update();
private:
    std::vector<registry_object> registry;
};

#endif
