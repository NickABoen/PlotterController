#ifndef WIRINGPICONTEXT_HPP
#define WIRINGPICONTEXT_HPP

namespace plotter{
    using pin = unsigned int;

    class context{
        /*Interface*/
        private:
        public:
            context(const context&) = delete;               // Delete the copy constructor
            context& operator=(const context&) = delete;    // Delete the default copy assignment
            context();
            ~context();

            void write(pin pin_number, bool value);
        
        /*Members*/
        private:
        public:

    };
}

#endif
