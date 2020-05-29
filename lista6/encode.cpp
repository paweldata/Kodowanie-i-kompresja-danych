#include "src/EncodeParameters.h"
#include "src/TGAImage.h"
#include "src/Encoder.h"

int main(int argc, char** argv) {
    EncodeParameters param = EncodeParameters(argc, argv);

    if (!param.ifCorrect()) {
        EncodeParameters::showError();
        return 1;
    }

    Encoder encoder = Encoder(TGAImage(param.input));
    encoder.createFilters();
    encoder.createDictionaries(param.getBitsNumber());

    encoder.writeDictionaryToFile(param.output, param.getBitsNumber());
    encoder.writeHeaderToFile(param.output);
    encoder.writeCodeToFile(param.output);

    param.input.close();
    param.output.close();

    return 0;
}
