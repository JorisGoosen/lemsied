#include <map>
#include <vector>

typedef size_t lemFrame;
typedef std::vector<lemFrame> lemAnim;

enum lemVisualState { wacht, stilO, stilRO, stilRB, stilB, stilLB, stilLO};

std::map<lemVisualState, std::map<lemVisualState, lemAnim> > visualTransitions;

void fillTransitions();
