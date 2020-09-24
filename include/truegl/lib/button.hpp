#ifndef _TBUTTON_HPP
#define _TBUTTON_HPP

#include <truegl/lib/widget.hpp>

namespace TGL
{
    class TButton : public TWidget
    {
    private:
    public:
        TButton();
        TButton(std::String title);
        TButton(char *title){
            
        }
        ~TButton();
    };
} // namespace TGL
#endif // !_TBUTTON_HPP