#pragma once

enum class Error
{
    NoError,
    CorruptedArchive, //не удалось заархивировать
    VariableBig, //если слишком много переменных
    DiffrentType //если при десеризации тип не uint_64 и не bool
};
