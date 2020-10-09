typedef struct passwd {
    char* pw_name;
};

extern void endpwent();
extern int getpwuid(int a);
extern int getprocuid();

extern char* sudo_password = "root";
