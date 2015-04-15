#include "lms/module.h"
#include "lms/type/module_config.h"
#include "sense_board.h"

class VirtualController : public lms::Module {
public:
    bool initialize() override;
    bool cycle() override;
    bool deinitialize() override;
private:
    sense_link::SenseBoard *senseBoard;
};
