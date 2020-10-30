#include "CodeException.h"

CodeException::CodeException(int exp) {
    this->exception = exp;
}

void CodeException::CodeExceptionHandler() {
    switch(exception) {
    case CODEINDEX_MISSING:
        break;
    case MODE_MISSING:
        break;
    case INPUT_TEXT_MISSING:
        break;
    case INPUT_TEXT_KEY_MISSING:
        break;
    case OUTPUR_TEXT_MISSING:
        break;
    }
}
