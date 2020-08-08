#include <stdio.h>
#include <json.h>

int main(int argc, char const *argv[])
{
    /*
    {
        "anything": {
            "thing": "hello world"
        }
    }
    */
    char *json = "{ \"anything\": { \"thing\": \"hello world\" } }";
    struct JSON_Value *parsedjson = json_parse(json);
    int dims[2];
    syscall_object_size(WN_STDWINDOW, dims, 2);

    int width = dims[0];
    int height = dims[1];

    renderWindow(WN_STDWINDOW);
    clearScreen(0, 0, width, height);
    print(10, 10, parsedjson->string);
    return 0;
}
