#pragma once
#ifndef PLOTTER_UNITS_HPP 
#define PLOTTER_UNITS_HPP

#include <ratio>

namespace plotter{
    template<class Ratio>
    constexpr double get_ratio(){
        return (static_cast<double>(Ratio::num) / static_cast<double>(Ratio::den));
    }

    constexpr double convert(double value, double from_ratio, double to_ratio){
        return value * (from_ratio / to_ratio);
    }

    template<class FromRatio, class ToRatio>
    constexpr double convert(double value){
        return value * get_ratio<std::ratio_divide<FromRatio,ToRatio>>();
    }

    template<class ToRatio>
    constexpr double convert(double value){
        return convert<std::ratio<1>, ToRatio>(value);
    }

    template<class Ratio=std::ratio<1>>
    class travel{
        public:
            using unit = Ratio;
            double value;
            travel(double v): value(v){}
    };

    class step{
        public:
            int value;
            step(int v): value(v){}
    };

    using millimeters = travel<std::milli>;
    using centimeters = travel<std::milli>;
    using decimeters = travel<std::milli>;
    using meters = travel<std::milli>;
    using decameters = travel<std::milli>;
    using hectometers = travel<std::milli>;
    using kilometers = travel<std::milli>;

    class bool_t{
        private:
            bool m_value;
        public:
            bool_t(): m_value(){}
            bool_t(bool value): m_value(value){}
            operator bool() const{return m_value;}
            bool* operator&(){return &m_value;}
            const bool* operator&() const{return &m_value;}
    };
}

constexpr double operator""_mm(long double v){return plotter::convert<std::milli>(v);}
constexpr double operator""_cm(long double v){return plotter::convert<std::centi>(v);}
constexpr double operator""_dm(long double v){return plotter::convert<std::deci>(v);}
constexpr double operator""_m(long double v){return plotter::convert<std::ratio<1>>(v);}
constexpr double operator""_dam(long double v){return plotter::convert<std::deca>(v);}
constexpr double operator""_hm(long double v){return plotter::convert<std::hecto>(v);}
constexpr double operator""_km(long double v){return plotter::convert<std::kilo>(v);}

#endif
