#include "src/DecodeParameters.h"
#include "src/Decoder.h"

int main(int argc, char** argv) {
    DecodeParameters param = DecodeParameters(argc, argv);

    if (!param.ifCorrect()) {
        DecodeParameters::showError();
        return 1;
    }

    Decoder decoder = Decoder();
    decoder.getDictionary(param.input);

    decoder.writeHeaderToFile(param.input, param.output);
    decoder.writePixelsToFile(param.input, param.output);

    param.input.close();
    param.output.close();

    return 0;
}
