#include <iostream>
#include <sstream>
#include <fstream>

// DEFINO EL NOMBRE DEL ARCHIVO QUE CREO POR COMODIDAD
#define CONSTANTE_DE_ARCHIVO "Estudiantes.csv"

using namespace std;

// FUNCION PARA VER SI ESTÁ PRESENTE O NO
string isStudentPresent(string present);

// CLASE ESTDUDIANTE
class Student
{
private:
    int identifier;
    string name, surname;

public:
    Student()
    {
        // cout << "Student construct" << endl
        //      << endl;
    }
    ~Student()
    {
        // cout << "Student deconstruct" << endl
        //      << endl;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setSurname(string surname)
    {
        this->surname = surname;
    }
    void setIdentifier(int identifier)
    {
        this->identifier = identifier;
    }
    string getName()
    {
        return name;
    }
    string getSurname()
    {
        return surname;
    }
    int getIdentifier()
    {
        return identifier;
    }
};

// CLASE CURSO
class Course
{
private:
    int identifier;
    string name;

public:
    Course()
    {
        // cout << "Course construct" << endl
        //      << endl;
    }
    ~Course()
    {
        // cout << "Course deconstruct" << endl
        //      << endl;
    }
    void setIdentifier(int identifier)
    {
        this->identifier = identifier;
    }
    void setName(string name)
    {
        this->name = name;
    }
    int getIdentifier()
    {
        return identifier;
    }
    string getName()
    {
        return name;
    }
};

// CLASE MANEJADOR DE ASISTENCIA
class AttendanceManagement
{
private:
    Student student;
    Course course;
    string datetime;
    bool state;

public:
    AttendanceManagement()
    {
        // cout << "AttendanceManagement construct" << endl
        //      << endl;
    }
    ~AttendanceManagement()
    {
        // cout << "AttendanceManagement deconstruct" << endl
        //      << endl;
    }
    void takeAttendance(Student student, Course course, string datetime, bool state)
    {
        // GUARDO LOS PARAMETROS EN LOS METODOS PRIVADOS DE LA CLASE
        this->student = student;
        this->course = course;
        this->datetime = datetime;
        this->state = state;

        // GUARDO EN ARCHIVO DE EXCEL
        ofstream crearArchivo;

        crearArchivo.open(CONSTANTE_DE_ARCHIVO);
        if (crearArchivo.is_open())
        {
            // ESTE ES EL ENCABEZADO
            crearArchivo << "Nombre"
                         << ";"
                         << "Apodo"
                         << ";"
                         << "DNI"
                         << ";"
                         << "Materia"
                         << ";"
                         << "Fecha"
                         << ";"
                         << "Presente"
                         << ";" << endl;
            // EL ";" ES EL QUE PERMITE QUE HAYA UN ESPACIO Y SE INGRESEN EN LA SIGUIENTE CELDA, ADEMAS ASÍ ES MAS FACIL DESPUES SABER LA DELIMITACIÓN
            crearArchivo << student.getName() << ";" << student.getSurname() << ";" << student.getIdentifier() << ";" << course.getName() << ";" << datetime << ";" << state;
        }
        crearArchivo.close();
        // DESCOMENTAR PARA ABRIR EL ARCHIVO EN EXCEL NO SE SI ABRE EN LINUX
        // ESTE ABRE EL EXCEL PERO HASTA NO CERRARLO NO CONTINUA EL PROCESO, FRENA EL PROCESO DE COMPILACIÓN DE C++
        system("Estudiantes.csv");
    }
    void showAttendance()
    {
        ifstream leerArchivo;
        leerArchivo.open(CONSTANTE_DE_ARCHIVO);
        string linea;
        char delimitador = ';';

        // SE LEE LA PRIMERA LINEA DEL EXCEL PARA DESCARTAR EL ENCABEZADO
        getline(leerArchivo, linea);
        // cout<<linea<<endl; DESCOMENTAR PARA VER LA PRIMERA LINEA DEL ARCHIVO DE EXCEL
        while (getline(leerArchivo, linea))
        {
            // SE CONVIERTE LA LINEA DE DATOS DE EXCEL EN UN STRING STREAM PARA SU POSTERIOR OBTENCIÓN DE DATOS Y ALOJARLOS EN VARIABLES
            stringstream stream(linea);
            string name, surname, course, date, is_present, id;
            // SE GUARDAN LOS DATOS EN VARIABLES HASTA LLEGAR A CIERTO DELIMITADOR SIENDO EL ;
            getline(stream, name, delimitador);
            getline(stream, surname, delimitador);
            getline(stream, id, delimitador);
            getline(stream, course, delimitador);
            getline(stream, date, delimitador);
            getline(stream, is_present, delimitador);
            // SE IMPRIMEN LOS DATOS
            cout << "Name " << name << endl;
            cout << "Surname " << surname << endl;
            cout << "Identification " << id << endl;
            cout << "Course " << course << endl;
            cout << "Date " << date << endl;
            cout << "Is present " << isStudentPresent(is_present) << endl;
        }
        leerArchivo.close();
    }
};

// FUNCION PARA VER SI ESTÁ PRESENTE O NO
string isStudentPresent(string present)
{
    if (stoi(present) == true)
    {
        return "Yes";
    }
    return "No";
}

int main()
{
    Student student;
    Course course;
    AttendanceManagement manager;
    // INGRESO LOS DATOS HARDCODEADOS
    student.setName("Tadeo");
    student.setSurname("Tadeus");
    student.setIdentifier(94583899);

    course.setIdentifier(69420);
    course.setName("Base de datos");

    manager.takeAttendance(student, course, "20/4/2023", true);
    manager.showAttendance();
    return 0;
}