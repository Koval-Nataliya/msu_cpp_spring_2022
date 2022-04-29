#pragma once
template <class T>
Error Deserializer::load(T& object){
    return object.serialize(*this);
}

template <class... ArgsT>
Error Deserializer::operator()(ArgsT&&... args){
    return process(args...);
}

template <class T, class... ArgsT>
Error Deserializer::process(T& value, ArgsT&&... args){
    Error err = process(value);
    if(err != Error::NoError)
        return err;
    return process(std::forward<ArgsT>(args)...);
}

template <class T>
Error Deserializer::process(T& value){
    bool is_bool = std::is_same<bool, T>::value;
    bool is_uint64_t = std::is_same<uint64_t, T>::value;
    if(!(is_bool || is_uint64_t))
        return Error::CorruptedArchive;
    std::string text;
    in_ >> text;
    if (text.empty())
        return Error::VariableBig;
    if (is_bool) {
        if (text == "true")
            value = true;
        else if (text == "false")
            value = false;
    } else {
        value = std::stoull(text);
    }
    return Error::NoError;
}
