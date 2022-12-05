#include <iostream>
#include <cstring>
#include <vector>
#include "chrono"
using namespace std;

class String{
private:
    char* data_;
    int size_ = 600; // я не хочу писать ресайз, вводить можно только строки в 60 символов
public:
    String() = default;
    String(const char* string){
        size_ = strlen(string);
        data_ = new char[size_];
        memcpy(data_, string, size_);
    }

    String(String& other){
        size_ = other.size_;
        data_ = new char[size_];
        memcpy(data_, other.data_, size_);
    }

    String(String&& other){
        size_ = other.size_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.size_ = 0;
    }

    ~String(){
        //printf("Deleted\n");
        delete[] data_;
    }

    String& operator= (String&& other){
        //printf("Moved\n");
        if (this != &other){
            delete[] data_;

            size_ = other.size_;
            data_ = other.data_;

            other.size_ = 0;
            other.data_ = nullptr;
        }
        return *this;
    }

    static void Swap_move(String* a, String* b){
        String temp = move(*a);
        *a = move(*b);
        *b = move(temp);
    }

    static void Swap_copy(String* a, String* b){
        String temp(*a);
        memcpy(temp.data_, a->data_, a->size_);

        a->size_ = b->size_;
        memcpy(a->data_, b->data_, b->size_);

        b->size_ = temp.size_;
        memcpy(b->data_, temp.data_, temp.size_);
    }

    void Print(){
        for (int i = 0; i < size_; i++){
            cout << data_[i];
        }
        cout << endl;
    }
};


int main() {
    int vector_size = 1000000;

    vector<String> string_vector(vector_size);

    string_vector[0] = "pointer..................................................... ........................................................... ........................................................... ........................................................... ........................................................... ........................................................... ........................................................... ........................................................... ...........................................................";
    for (int i = 1; i < vector_size; i++){
        string_vector[i] = "............................................................ ........................................................... ........................................................... ........................................................... ........................................................... ........................................................... ........................................................... ........................................................... ...........................................................";
    }

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);


    // COPY SWAP
    begin = std::chrono::steady_clock::now();
    for (int i = 1; i<vector_size; i++){
        String::Swap_copy(&(string_vector[i-1]), &(string_vector[i]));
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "COPY SWAP: " << elapsed_ms.count() << " ms\n\n";

   /* for (int i = 0; i<vector_size; i++){
        printf("%3d: ", i);
        string_vector[i].Print();
    }*/

    // MOVE SWAP
    begin = std::chrono::steady_clock::now();
    for (int i = vector_size - 1; i > 0; i--){
        String::Swap_move(&(string_vector[i-1]), &(string_vector[i]));
    }
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "MOVE SWAP: " << elapsed_ms.count() << " ms\n\n";

    /*for (int i = 0; i<vector_size; i++){
        printf("%3d: ", i);
        string_vector[i].Print();
    }*/



    return 0;
}
