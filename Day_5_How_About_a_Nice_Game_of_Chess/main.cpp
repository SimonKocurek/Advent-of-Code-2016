#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <crypto++/md5.h>
#include <cryptopp/hex.h>
#include <iostream>

std::string concat_with_index(int& index, const std::string& seed) {
    std::string result = seed + std::to_string(index);
    index++;
    
    return result;
}

std::string calculate_hash(byte* digest, std::string& seed) {
    CryptoPP::Weak::MD5 hash;
    hash.CalculateDigest(digest, (const byte*) seed.c_str(), seed.length());
    
    CryptoPP::HexEncoder encoder;
    std::string output;
    
    encoder.Attach( new CryptoPP::StringSink( output ));
    encoder.Put( digest, sizeof(digest));
    encoder.MessageEnd();
    
    return output;
}

bool correct_hash(std::string& hash) {
    for (int i = 0; i < 5; i++) {
        if (hash[i] != '0') {
            return false;
        }
    }
    
    return true;
}

int get_position(std::string& hash) {
    char position = hash[5];
    
    if ('0' <= position && '7' >= position) {
        return position - '0';
    }
    
    return -1;
}

bool write_to_password(std::string& hash, bool written[8], char password[8]) {
    int position = get_position(hash);

    if (position == -1 || written[position]) {
        return false;
    }

    password[position] = hash[6];
    written[position] = true;
    
    return true;
}

int main(int argc, char** argv) {
    byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];
    const std::string seed = "ffykfhsq";
    int index = 0;
    
    char password[8];
    bool written[8] = {0};
    int written_count = 0;
    
    while (written_count < 8) {
        std::string temp_seed = concat_with_index(index, seed);
        std::string hash = calculate_hash(digest, temp_seed);
        
        while (!correct_hash(hash)) {
            temp_seed = concat_with_index(index, seed);
            hash = calculate_hash(digest, temp_seed);
        }
        
        if (write_to_password(hash, written, password)) {
            written_count++;
        }
    }
    
    std::cout << password;
    
    return 0;
}
