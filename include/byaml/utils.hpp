namespace byaml::utils {


template<typename... Ts>
struct Overloaded: public Ts... {
    using Ts::operator()...;
};

template<typename... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;


}

