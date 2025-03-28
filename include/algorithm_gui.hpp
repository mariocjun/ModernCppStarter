#ifndef IMALGORITHM_ALGORITHM_GUI_HPP
#define IMALGORITHM_ALGORITHM_GUI_HPP

#include <imgui.h>
#include "imgui_internal.h"

#include "utils/imvec_operators.hpp"

namespace ImAlgorithm {

class AlgorithmGUI {
public:
    virtual void show(ImVec2 pos, ImVec2 size) = 0;
    virtual const char * name() const = 0;
};

}  // namespace ImAlgorithm

#endif  // IMALGORITHM_ALGORITHM_GUI_HPP