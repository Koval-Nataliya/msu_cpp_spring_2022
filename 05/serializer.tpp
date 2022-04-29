#pragma once
template <class T>
Error Serializer::save(T& object){       
    return object.serialize(*this);
}

template <class... ArgsT>
Error Serializer::operator()(ArgsT... args){
    return process(args...);
}

template <class T, class... ArgsT>
Error Serializer::process(T val, ArgsT&&... args){
    Error err = process(val);
    if(err != Error::NoError)
        return err;
    return process(std::forward<ArgsT>(args)...);
}

template <class T>
Error Serializer::process(T val){
    bool is_bool = std::is_same<bool, T>::value;
    bool is_uint64_t = std::is_same<uint64_t, T>::value;
    if(!(is_bool || is_uint64_t))
        return Error::CorruptedArchive;
    if (is_bool) {
        std::string val_ = val == 1 ? "true" : "false";
        out_ << val_;
    } else {
        out_ << val;
    }
    out_ << Separator;
    return Error::NoError;
}
