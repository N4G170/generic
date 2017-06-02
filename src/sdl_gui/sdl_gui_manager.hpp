#ifndef SDL_GUI_MANAGER_HPP
#define SDL_GUI_MANAGER_HPP

class GuiManager
{
    public:
        /* Default constructor */
        GuiManager();
        /* Default destructor */
        virtual ~GuiManager() noexcept;

        /* Copy constructor */
        GuiManager(const GuiManager& other);
        /* Move constructor */
        GuiManager(GuiManager&& other) noexcept;

        /* Copy operator */
        GuiManager& operator= (const GuiManager& other);
        /* Move operator */
        GuiManager& operator= (GuiManager&& other) noexcept;

    private:
        // vars and stuff
};

#endif //GUI_MANAGER_HPP
