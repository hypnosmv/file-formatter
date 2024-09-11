#pragma once


enum ExitCode : int
{
    SUCCESS = 0,
    INVALID_ARGS_NUMBER = 1,
    READ_FAIL = 2,
    WRITE_FAIL = 3,
    INVALID_CONFIG = 4,
    INVALID_FINDER_NAME = 5,
    INVALID_FORMATTER_NAME = 6,
};
