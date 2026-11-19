typedef struct {
    char nume[30];
    int varsta;
    char grupa[6];
    char cnp[6];
    float media;
} Student;

typedef struct {
    int grupa;
} Grupa;

#define N 40

const char *nume[N] = {
    "Popescu Andrei",
    "Ionescu Maria",
    "Stan Alexandru",
    "Dumitrescu Ioana",
    "Marin Vlad",
    "Tudor Elena",
    "Radu Mihai",
    "Stoica Ana",
    "Dobre David",
    "Enache Gabriel",
    "Matei Bianca",
    "Popescu Cristian",
    "Mihai Daria",
    "Neagu Stefan",
    "Ilie Andreea",
    "Munteanu Robert",
    "Ionescu Irina",
    "Sandu Victor",
    "Stan Sofia",
    "Gheorghe Andrei",
    "Constantin Eduard",
    "Moldovan Alexandra",
    "Dinu George",
    "Vasile Cristina",
    "Barbu Florin",
    "Diaconu Natalia",
    "Popescu Tudor",
    "Marin Sebastian",
    "Pavel Daniela",
    "Dumitru Rares",
    "Georgescu Teodora",
    "Oprea Adrian",
    "Toma Maria",
    "Serban Catalin",
    "Nita Gabriela",
    "Rusu Matei",
    "Lazar Ioana",
    "Dragomir Alexandru",
    "Preda Vlad",
    "Sandu Diana"
};

int varste[N] = {
    19, 20, 22, 21, 19,
    20, 23, 22, 19, 21,
    20, 22, 19, 21, 23,
    20, 22, 21, 19, 23,
    20, 19, 21, 22, 23,
    19, 20, 21, 22, 20,
    19, 23, 21, 20, 22,
    19, 21, 23, 20, 22
};

const char *cnp[N] = {
    "1000000001", "1000000002", "1000000003", "1000000004",
    "1000000005", "1000000006", "1000000007", "1000000008",
    "1000000009", "1000000010", "1000000011", "1000000012",
    "1000000013", "1000000014", "1000000015", "1000000016",
    "1000000017", "1000000018", "1000000019", "1000000020",
    "1000000021", "1000000022", "1000000023", "1000000024",
    "1000000025", "1000000026", "1000000027", "1000000028",
    "1000000029", "1000000030", "1000000031", "1000000032",
    "1000000033", "1000000034", "1000000035", "1000000036",
    "1000000037", "1000000038", "1000000039", "1000000040"
};

const char *grupe[N] = {
    "314CB", "321CA", "342CC", "331CB", "314CB",
    "322CC", "341CA", "342CC", "311CA", "331CB",
    "321CA", "341CA", "311CA", "332CC", "342CC",
    "322CC", "341CA", "332CC", "314CB", "342CC",
    "321CA", "311CA", "332CC", "341CA", "342CC",
    "314CB", "322CC", "331CB", "341CA", "321CA",
    "311CA", "342CC", "332CC", "322CC", "341CA",
    "314CB", "331CB", "342CC", "321CA", "341CA"
};

float medii[N] = {
    9.50, 8.70, 4.30, 7.80, 6.50,
    9.80, 5.20, 8.70, 4.80, 7.30,
    10.0, 6.40, 8.20, 9.50, 5.00,
    3.90, 9.80, 7.60, 6.50, 8.90,
    7.20, 9.40, 5.60, 8.30, 4.20,
    9.10, 8.70, 6.80, 10.0, 7.50,
    5.00, 3.50, 9.50, 8.20, 6.70,
    4.90, 9.80, 7.40, 5.80, 8.60
};