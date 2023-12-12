#include <iostream>
#include <string.h>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <locale>
#include <vector>
#include <limits>


using namespace std;

// Prototipos de funciones
void menu();
void visualizar_info_peli();
void filtrar_peliculas();
void agregar_peliculas();
void registrar_clientes();
void buscar_clientes();
void rentar_peliculas();
void consultar_estado_peli();
void borrar_peliculas();
void borrar_cliente();
void devolver_pelicula();

// Función para ver la información de las películas
void visualizar_info_peli() {
    ifstream archivo("movies.csv");

    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
        return;  // Salir si el archivo no se puede abrir
    }

    int num_peliculas;
    cout << "Ingrese el numero de peliculas que desea ver: ";
    while (!(cin >> num_peliculas) || num_peliculas <= 0) {
        cout << "Por favor, ingrese un numero valido y mayor a cero: ";
        cin.clear();  // Limpiar el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descartar la entrada incorrecta
    }

    for (int i = 0; i < num_peliculas; ++i) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer de entrada

        string pelicula_buscar;
        cout << "Ingrese el nombre de la pelicula #" << (i + 1) << ": ";
        getline(cin, pelicula_buscar);

        bool pelicula_existe = false;
        string linea;

        // Restablecer al inicio del archivo en cada iteración
        archivo.clear();
        archivo.seekg(0, ios::beg);

        while (getline(archivo, linea)) {
            stringstream llave(linea);
            string id, movie, genders, duration, director, price, release_on, rent_to, rent_on, status;

            getline(llave, id, ';');
            getline(llave, movie, ';');
            getline(llave, genders, ';');
            getline(llave, duration, ';');
            getline(llave, director, ';');
            getline(llave, price, ';');
            getline(llave, release_on, ';');
            getline(llave, rent_to, ';');
            getline(llave, rent_on, ';');
            getline(llave, status, ';');

            if (pelicula_buscar == movie) {
                pelicula_existe = true;

                cout << endl << "ID: " << id << endl;
                cout << "Pelicula: " << movie << endl;

                cout << "Que campos desea visualizar?"<<endl;
                cout<<"Escribalos separados por comas: (id, movie, genders, duration, director, price, release_on, rent_to, rent_on, status): "<<endl << endl;
                string campos;
                getline(cin, campos);

                stringstream campos_ss(campos);
                string campo;
                while (getline(campos_ss, campo, ',')) {
                    campo.erase(remove_if(campo.begin(), campo.end(), ::isspace), campo.end());
                    if (campo == "id") cout << "ID: " << id << endl;
                    else if (campo == "movie") cout << "Pelicula: " << movie << endl;
                    else if (campo == "genders") cout << "Genero: " << genders << endl;
                    else if (campo == "duration") cout << "Duracion: " << duration << " min" << endl;
                    else if (campo == "director") cout << "Director: " << director << endl;
                    else if (campo == "price") cout << "Precio: " << price << "$"<< endl;
                    else if (campo == "release_on") cout << "Fecha de lanzamiento: " << release_on << endl;
                    else if (campo == "rent_to") cout << "Alquilada a: " << rent_to << endl;
                    else if (campo == "rent_on") cout << "Fecha de Alquiler: " << rent_on << endl;
                    else if (campo == "status") cout << "Estado: " << status << endl;
                    else cout << "Campo desconocido. Ingresa uno valido: " << campo << endl;
                }
                break;
            }
        }

        if (!pelicula_existe) {
            cout << "La pelicula '" << pelicula_buscar << "' no se encuentra en la base de datos." << endl;
        }

        // Volver al principio del archivo para la próxima película
        archivo.clear();
        archivo.seekg(0, ios::beg);
    }

    archivo.close();
}


//Funcion para filtrar peliculas
void filtrar_peliculas() {
    int opc;
    while(true) {
        cout << "---------------Filtrar Peliculas---------------" << endl;
        cout << "1. Por Genero" << endl;
        cout << "2. Por Duracion" << endl;
        cout << "3. Por Director" << endl;
        cout << "4. Por Precio" << endl;
        cout << "5. Por Fecha de Lanzamiento" << endl;
        cout << "6. Regresar al menu principal" << endl;
        cout << "Selecciona una opcion: ";
        
        if (!(cin >> opc)) {
            cout << "Por favor, ingresa un número válido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (opc < 1 || opc > 6) {
            cout << "Opción no válida. Inténtalo de nuevo." << endl;
            continue;
        }

        if (opc == 6) break; // Salir del bucle si se selecciona regresar al menú principal

        cout << " " << endl;

        switch (opc) {
            case 1: {
                ifstream archivo("movies.csv", ios::in);

                if (!archivo) {
                    cout << "No se puede abrir el archivo" << endl;
                } 
                else {
                    string linea;
                    string id, movie, genders, duration, director, price, release_on, rent_on, rent_to, status;
                    string genero_buscar;
                    
                    cout << "Ingrese el genero a buscar: ";
                    cin.ignore(); // Ignorar el salto de línea anterior
                    getline(cin, genero_buscar);

        // Validación de la entrada del género
        if (genero_buscar.empty()) {
            cout << "El género ingresado no es válido. Inténtalo de nuevo." << endl;
            break;
        }

        bool genero_encontrado = false;

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, id, ';');
            getline(llave, movie, ';');
            getline(llave, genders, ';');
            getline(llave, duration, ';');
            getline(llave, director, ';');
            getline(llave, price, ';');
            getline(llave, release_on, ';');
            getline(llave, rent_to, ';');
            getline(llave, rent_on, ';');
            getline(llave, status, ';');

            // Buscar el género en la lista de géneros de la película
            if (genero_buscar.compare(genders)==0) {
                genero_encontrado = true;
                cout << "ID: " << id << endl;
                cout << "Pelicula: " << movie << endl;
                cout << "Duracion: " << duration << " min" << endl;
                cout << "Genero: " << genders << endl;
                cout << "Director: " << director << endl;
                cout << "Precio: " << price << "$" << endl;
                cout << "Fecha de lanzamiento: " << release_on << endl;
                cout << "Alquida a: " << rent_to << endl;
                cout << "Fecha de alquiler: " << rent_on << endl;
                cout << "Estado: " << status << endl << endl;
            }
        }

        archivo.close();

        if (!genero_encontrado) {
            cout << "No se encontraron peliculas con el genero: " << genero_buscar << endl << endl;
        }
    }
    break;
}
            case 2: {
    ifstream archivo("movies.csv", ios::in);
    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string id, movie, genders, duration, director, price, release_on, rent_on, rent_to, status;
        string duracion_buscar;

        cout << "Ingrese la duracion de la pelicula en minutos: ";
        cin.ignore(); // Ignorar el salto de línea anterior
        getline(cin, duracion_buscar);

        // Validación de la entrada de duración
        if (duracion_buscar.empty() || !all_of(duracion_buscar.begin(), duracion_buscar.end(), ::isdigit)) {
            cout << "La duración ingresada no es válida. Debe ser un número. Inténtalo de nuevo." << endl;
            break;
        }

        bool duracion_encontrada = false;

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, id, ';');
            getline(llave, movie, ';');
            getline(llave, genders, ';');
            getline(llave, duration, ';');
            getline(llave, director, ';');
            getline(llave, price, ';');
            getline(llave, release_on, ';');
            getline(llave, rent_to, ';');
            getline(llave, rent_on, ';');
            getline(llave, status, ';');

            if (duracion_buscar.compare(duration) == 0) {
                duracion_encontrada = true;
                cout << "ID: " << id << endl;
                cout << "Pelicula: " << movie << endl;
                cout << "Duracion: " << duration << " min" << endl;
            }
        }

        archivo.close();
        if (!duracion_encontrada) {
            cout << "No se encontraron peliculas con una duracion de: " << duracion_buscar << " minutos." << endl << endl;
        }
    }
    break;
}

            case 3: {
    ifstream archivo("movies.csv", ios::in);
    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string id, movie, genders, duration, director, price, release_on, rent_on, rent_to, status;
        string director_buscar;

        cout << "Ingrese el nombre completo del director a buscar: ";
        cin.ignore(); // Ignorar el salto de línea anterior
        getline(cin, director_buscar);

        // Validación de la entrada del director
        if (director_buscar.empty()) {
            cout << "El nombre del director ingresado no es válido. Inténtalo de nuevo." << endl;
            break;
        }

        bool director_encontrado = false;

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, id, ';');
            getline(llave, movie, ';');
            getline(llave, genders, ';');
            getline(llave, duration, ';');
            getline(llave, director, ';');
            getline(llave, price, ';');
            getline(llave, release_on, ';');
            getline(llave, rent_to, ';');
            getline(llave, rent_on, ';');
            getline(llave, status, ';');

            if (director_buscar.compare(director) == 0) {
                director_encontrado = true;
                cout << "Director: " << director << endl;
                cout << "ID: " << id << endl;
                cout << "Pelicula: " << movie << endl;
                cout << "Duracion: " << duration << " min" << endl;
                cout << "Precio: " << price << "$" << endl;
                cout << "Fecha de lanzamiento: " << release_on << endl;
                cout << "Alquilada a: " << rent_to << endl;
                cout << "Fecha de alquiler: " << rent_on << endl;
                cout << "Estado: " << status << endl << endl;
            }
        }

        archivo.close();

        if (!director_encontrado) {
            cout << "No se encontraron películas del director: " << director_buscar << endl << endl;
        }
    }
    break;
}

            case 4: {
    ifstream archivo("movies.csv", ios::in);
    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string id, movie, genders, duration, director, price, release_on, rent_to, rent_on, status;
        string precio_ingresado;
        
        cout << "Ingrese el precio para ver las peliculas: ";
        cin >> precio_ingresado;

        // Validación de la entrada de precio
        if (precio_ingresado.empty() || !all_of(precio_ingresado.begin(), precio_ingresado.end(), [](char c){ return isdigit(c) || c == '.'; })) {
            cout << "El precio ingresado no es válido. Inténtalo de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        bool precio_encontrado = false;

        while (getline(archivo, linea)) {
            stringstream llave(linea);
            getline(llave, id, ';');
            getline(llave, movie, ';');
            getline(llave, genders, ';');
            getline(llave, duration, ';');
            getline(llave, director, ';');
            getline(llave, price, ';');
            getline(llave, release_on, ';');
            getline(llave, rent_to, ';');
            getline(llave, rent_on, ';');
            getline(llave, status, ';');

            if (precio_ingresado == price) {
                precio_encontrado = true;
                cout << "ID: " << id << endl;
                cout << "Pelicula: " << movie << endl;
                cout << "Precio: " << price << "$" << endl;
                cout << "Duracion: " << duration << "min" << endl;
            }
        }

        archivo.close();

        if (!precio_encontrado) {
            cout << "No se encontraron películas con precio de " << precio_ingresado << "$." << endl << endl;
        }
    }
    break;
}

            case 5: {
    ifstream archivo("movies.csv", ios::in);
    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string id, movie, genders, duration, director, price, release_on, rent_to, rent_on, status;

        int filtroFecha;
        cout << "Buscar por: 1. Fecha completa, 2. Mes, 3. Año" << endl;
        cout << "Selecciona una opción: ";
        cin >> filtroFecha;

        if (filtroFecha < 1 || filtroFecha > 3) {
            cout << "Opción no válida. Inténtalo de nuevo." << endl;
            break;
        }

        string fecha_buscar;
        cout << "Ingresa ";
        if (filtroFecha == 1) {
            cout << "la fecha completa (formato YYYY-MM-DD): ";
        } else if (filtroFecha == 2) {
            cout << "el mes (formato MM): ";
        } else {
            cout << "el año (formato YYYY): ";
        }
        cin.ignore();
        getline(cin, fecha_buscar);

        if (fecha_buscar.empty() || (filtroFecha == 1 && fecha_buscar.length() != 10) || (filtroFecha == 2 && fecha_buscar.length() != 2) || (filtroFecha == 3 && fecha_buscar.length() != 4)) {
            cout << "Entrada no válida. Inténtalo de nuevo." << endl;
            break;
        }

        bool fecha_encontrada = false;

        while (getline(archivo, linea)) {
            stringstream llave(linea);
            getline(llave, id, ';');
            getline(llave, movie, ';');
            getline(llave, genders, ';');
            getline(llave, duration, ';');
            getline(llave, director, ';');
            getline(llave, price, ';');
            getline(llave, release_on, ';');
            getline(llave, rent_to, ';');
            getline(llave, rent_on, ';');
            getline(llave, status, ';');

            string fecha_comparar = release_on;
            if (filtroFecha == 2) {
                fecha_comparar = fecha_comparar.substr(5, 2); // Extrae el mes
            } else if (filtroFecha == 3) {
                fecha_comparar = fecha_comparar.substr(0, 4); // Extrae el año
            }

            if (fecha_buscar == fecha_comparar) {
                fecha_encontrada = true;
                cout << "ID: " << id << endl;
                cout << "Pelicula: " << movie << endl;
                cout << "Duracion: " << duration << " min" << endl;
                cout << "Precio: " << price << "$" << endl;
                cout << "Director: " << director << endl;
                cout << "Fecha de Lanzamiento: " << release_on << endl;
            }
        }

        archivo.close();

        if (!fecha_encontrada) {
            cout << "No se ha encontrado ninguna película con esa fecha de lanzamiento." << endl << endl;
        }
    }
    break;
}

            default:
                cout << "Opcion no valida. Intentalo de nuevo." << endl;
                break;
        }
    }
}
bool existe_pelicula(const string& id, const string& movie, ifstream& archivo) {
    string linea;
    while (getline(archivo, linea)) {
        stringstream llave(linea);
        string current_id, current_movie;
        getline(llave, current_id, ';');
        getline(llave, current_movie, ';');
        if (!id.empty() && id == current_id) {
            return true; // La película ya existe con el mismo ID
        }
        if (!movie.empty() && movie.compare(current_movie) == 0) {
            return true; // La película ya existe con el mismo nombre
        }
    }
    return false; // La película no existe
}

void agregar_peliculas(){

    ifstream lectura("movies.csv", ios::in);
    ofstream escritura("movies.csv", ios::app); // Abre el archivo en modo append

    if (!lectura || !escritura) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string id, movie, genders, duration, director, price, release_on, status;

        cout << "Ingrese el ID de la pelicula: ";
        cin >> id;
        cin.ignore(); // Limpiar el buffer de entrada

        // Verificar si el ID ya existe en otra película
        if (existe_pelicula(id, "", lectura)) {
            cout << "Ya existe una pelicula con el ID ingresado. Por favor, elija otro ID." << endl;
            return;
        }

        cout << "Ingrese el nombre de la pelicula: ";
        getline(cin, movie);

        // Verificar si el nombre ya existe en otra película
        if (existe_pelicula(movie,"", lectura)) {
            cout << "Ya existe una pelicula con el nombre ingresado. Por favor, elija otro nombre." << endl;
            return;
        }

        cout << "Ingrese el genero de la pelicula: ";
        getline(cin, genders);

        cout << "Ingrese la duracion de la pelicula en minutos: ";
        getline(cin, duration);

        cout << "Ingrese el director de la pelicula: ";
        getline(cin, director);

        cout << "Ingrese el precio de la pelicula: ";
        getline(cin, price);

        cout << "Ingrese la fecha de lanzamiento (YYYY-MM-DD): ";
        getline(cin, release_on);

        status = "Disponible";

        // Escribir la información de la película en el archivo con fechas por defecto y el estado "disponible"
        escritura << id << ';' << movie << ';' << genders << ';' << duration << ';' << director << ';'
                  << price << ';' << release_on << ";;"<< ';' << status << '\n';

        cout << "Pelicula agregada correctamente al archivo." << endl;
    }

    lectura.close();
    escritura.close();

}

bool existe_cliente(const string& id_client, ifstream& archivo) {
    string linea;
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string current_id;
        getline(ss, current_id, ';');
        if (id_client == current_id) {
            return true; // El cliente ya existe con el mismo ID
        }
    }
    return false; // El cliente no existe
}


void registrar_clientes(){

    ofstream archivo_clientes("clientes.csv", ios::app);
    if (!archivo_clientes) {
        cout << "No se puede abrir el archivo de clientes" << endl;
        return;
    }

    string id_client, name_client;
    cout << "Ingrese su ID: ";
    cin >> id_client;
    cin.ignore(); // Limpiar el buffer de entrada

    // Verificar si el ID ya existe en otro cliente
    ifstream lectura_clientes("clientes.csv", ios::app);
    if (existe_cliente(id_client, lectura_clientes)) {
        cout << "Ya existe un cliente con el ID ingresado. Por favor, elija otro ID." << endl;
        return;
    }
    lectura_clientes.close();

    cout << "Ingrese su nombre: ";
    getline(cin, name_client);

    // Escribir la información del cliente en el archivo CSV
    archivo_clientes << id_client << ';' << name_client << ';' << '\n';

    cout << " Ha sido registrado correctamente." << endl;
    archivo_clientes.close();

}

void rentar_peliculas() {
    vector<string> peliculas;
    vector<string> clientes;
    string linea;

    // Leer el archivo de películas
    ifstream archivo_peliculas("movies.csv");
    if (!archivo_peliculas.is_open()) {
        cout << "Error al abrir el archivo de películas." << endl;
        return;
    }
    while (getline(archivo_peliculas, linea)) {
        peliculas.push_back(linea);
    }
    archivo_peliculas.close();

    // Leer el archivo de clientes
    ifstream archivo_clientes("clientes.csv");
    if (!archivo_clientes.is_open()) {
        cout << "Error al abrir el archivo de clientes." << endl;
        return;
    }
    while (getline(archivo_clientes, linea)) {
        clientes.push_back(linea);
    }
    archivo_clientes.close();

    string id_cliente, nombre_pelicula, fecha_renta;
    cout << "Ingrese su ID de cliente: ";
    cin >> id_cliente;

    // Validar ID de cliente
    if (id_cliente.empty()) {
        cout << "ID de cliente inválido." << endl;
        return;
    }

    bool cliente_encontrado = false, cliente_sin_rentas = true;
    for (string& cliente : clientes) {
        stringstream ss(cliente);
        string id, nombre, peliculas_rentadas;
        getline(ss, id, ';');
        getline(ss, nombre, ';');
        getline(ss, peliculas_rentadas);

        if (id == id_cliente) {
            cliente_encontrado = true;
            if (!peliculas_rentadas.empty()) {
                cliente_sin_rentas = false;
                break;
            }
        }
    }

    if (!cliente_encontrado) {
        cout << "Cliente no encontrado. Por favor, regístrese para poder rentar una película." << endl;
        return;
    }

    if (!cliente_sin_rentas) {
        cout << "El cliente ya tiene películas rentadas. No puede rentar más películas hasta devolver las actuales." << endl;
        return;
    }

    cout << "Ingrese el nombre de la película que desea rentar: ";
    cin.ignore();
    getline(cin, nombre_pelicula);

    // Validar nombre de la película
    if (nombre_pelicula.empty()) {
        cout << "Nombre de película inválido." << endl;
        return;
    }

        bool pelicula_encontrada = false;
    for (string& pelicula : peliculas) {
        stringstream ss(pelicula);
        string id, movie, genders, duration, director, price, release_on, rent_to, rent_on, status;
        getline(ss, id, ';');
        getline(ss, movie, ';');
        getline(ss, genders, ';');
        getline(ss, duration, ';');
        getline(ss, director, ';');
        getline(ss, price, ';');
        getline(ss, release_on, ';');
        getline(ss, rent_to, ';'); // Este campo será actualizado
        getline(ss, rent_on, ';'); // Este campo será actualizado
        getline(ss, status, ';');  // Este campo será actualizado

        if (movie == nombre_pelicula && status != "rentada") {
            pelicula_encontrada = true;
            cout << "Ingrese la fecha de renta (YYYY-MM-DD): ";
            cin >> fecha_renta;

            // Validar fecha de renta
            if (fecha_renta.empty()) {
                cout << "Fecha de renta inválida." << endl;
                return;
            }

            // Reconstruir la línea de la película con la información actualizada
            pelicula = id + ";" + movie + ";" + genders + ";" + duration + ";" + director + ";" + price + ";" + release_on + ";" + id_cliente + ";" + fecha_renta + ";" + "rentada";
            break;
        }
    }


    if (!pelicula_encontrada) {
        cout << "Película no encontrada o ya está alquilada." << endl;
        return;
    }

    // Actualizar información del cliente
    for (string& cliente : clientes) {
        stringstream ss(cliente);
        string id, nombre, peliculas_rentadas;
        getline(ss, id, ';');
        getline(ss, nombre, ';');
        getline(ss, peliculas_rentadas);

        if (id == id_cliente) {
            if (!peliculas_rentadas.empty()) {
                peliculas_rentadas += ", ";
            }
            peliculas_rentadas += nombre_pelicula;
            cliente = id + ";" + nombre + ";" + peliculas_rentadas;
            break;
        }
    }

    // Guardar la información actualizada en los archivos
    ofstream salida_peliculas("movies.csv");
    for (const string& pelicula : peliculas) {
        salida_peliculas << pelicula << endl;
    }
    salida_peliculas.close();

    ofstream salida_clientes("clientes.csv");
    for (const string& cliente : clientes) {
        salida_clientes << cliente << endl;
    }
    salida_clientes.close();

    cout << "La película ha sido rentada exitosamente y el registro del cliente ha sido actualizado." << endl;
}



void buscar_clientes() {
    int op;
    bool entradaValida;

    do {
        entradaValida = true;
        cout << "1. Buscar cliente por ID. " << endl;
        cout << "2. Buscar cliente por nombre. " << endl;
        cout << "3. Regresar al menu. " << endl;
        cin >> op;

        // Validación de la entrada
        if(cin.fail()) {
            cin.clear(); // Limpia el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora la entrada incorrecta
            cout << "Por favor, ingrese un número válido." << endl;
            entradaValida = false;
        }

    } while (!entradaValida);

    switch (op) {
        //Buscar por ID
        case 1: {
    ifstream archivo("clientes.csv", ios::in);
    if(!archivo) {
        cout << "No se pudo abrir el archivo" << endl;
    } else {
        string linea;
        string id_client, name, rented_movies;
        string id_buscar;
        bool id_encontrado = false;

        cout << "Ingrese el id del cliente a buscar: " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el '\n' dejado por la última entrada
        getline(cin, id_buscar);

        while(getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, id_client, ';');
            getline(llave, name, ';');
            getline(llave, rented_movies, ';');

            if(id_buscar.compare(id_client) == 0) {
                cout << "ID: " << id_client << endl;
                cout << "Nombre: " << name << endl;
                cout << "Peliculas rentadas: " << rented_movies << endl;
                id_encontrado = true;
                break; // Salir del bucle después de encontrar el cliente
            }
        }

        archivo.close();

        if (!id_encontrado) {
            cout << "El cliente con id: " << id_buscar << " no existe" << endl << endl;
        }
    }
    break;
}
        //Buscar por Nombre
        case 2: {
    ifstream archivo("clientes.csv", ios::in);
    if(!archivo) {
        cout << "No se pudo abrir el archivo" << endl;
    } else {
        string linea;
        string id_client, name, rented_movies;
        string nombre_buscar;
        bool nombre_encontrado = false;

        cout << "Ingrese el nombre del cliente a buscar: " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora el '\n' dejado por la última entrada
        getline(cin, nombre_buscar);

        while(getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, id_client, ';');
            getline(llave, name, ';');
            getline(llave, rented_movies, ';');

            if(nombre_buscar.compare(name) == 0) {
                cout << "ID: " << id_client << endl;
                cout << "Nombre: " << name << endl;
                cout << "Peliculas rentadas: " << rented_movies << endl;
                nombre_encontrado = true;
                break; // Salir del bucle después de encontrar el cliente
            }
        }

        archivo.close();

        if (!nombre_encontrado) {
            cout << "El cliente con nombre: " << nombre_buscar << " no existe" << endl << endl;
        }
    }
    break;
}


        case 3:
            menu();
            break;

        default:
            cout << "Seleccione una opcion correcta." << endl;
            break;
    }
}

void borrar_peliculas(){
    ifstream archivo("movies.csv", ios::in);
    if(!archivo){
        cout<<"Error al abrir el archivo."<<endl<<endl;
    }else{
        vector<string> registros_no_eliminar;
        string linea;
        string id,movie,genders,duration,director,price,release_on,rent_to,rent_on,status;
        string id_peli_eliminar;
        cout<<"Ingrese el numero de ID de la pelicula a eliminar: "<<endl;
        cin>>id_peli_eliminar;
        bool existe = false;

        while(getline(archivo, linea)){
            //cout<<registro<<endl;
            stringstream llave(linea);

            getline(llave, id, ';');
            getline(llave, movie, ';');
            getline(llave, genders, ';');
            getline(llave, duration, ';');
            getline(llave, director, ';');
            getline(llave, price, ';');
            getline(llave, release_on, ';');
            getline(llave, rent_to, ';');
            getline(llave, rent_on, ';');
            getline(llave, status, ';');

            if(id_peli_eliminar.compare(id) == 0) existe = true;
            else registros_no_eliminar.push_back(linea);
        }//fin del while

        archivo.close();

        if(existe){//if(existe == true)
            ofstream nuevo("movies.csv");
            for(int i = 0; i < int(registros_no_eliminar.size()); i++){
                 nuevo<<registros_no_eliminar[i]<<endl;
            }
            nuevo.close();
            cout<<"Se elimino la pelicula correctamente"<<endl<<endl;
        }else{
            cout<<"La pelicula con numero de ID "<<id_peli_eliminar<<
                  " no existe en el archivo"<<endl<<endl;
        }
    }
}

void borrar_cliente() {
    ifstream archivo("clientes.csv", ios::in);
    if(!archivo){
        cout<<"Error al abrir el archivo."<<endl<<endl;
    }else{
        vector<string> registros_no_eliminar;
        string linea;
        string id_client, name, rented_movies;
        string id_cliente_eliminar;
        cout<<"Ingrese el numero de ID del cliente a eliminar: "<<endl;
        cin>>id_cliente_eliminar;
        bool existe = false;

        while(getline(archivo, linea)){
            //cout<<registro<<endl;
            stringstream llave(linea);

            getline(llave, id_client, ';');
            getline(llave, name, ';');
            getline(llave, rented_movies, ';');

            if(id_cliente_eliminar.compare(id_client) == 0) existe = true;
            else registros_no_eliminar.push_back(linea);
        }//fin del while

        archivo.close();

        if(existe){//if(existe == true)
            ofstream nuevo("clientes.csv");
            for(int i = 0; i < int(registros_no_eliminar.size()); i++){
                 nuevo<<registros_no_eliminar[i]<<endl;
            }
            nuevo.close();
            cout<<"Se elimino el cliente correctamente"<<endl<<endl;
        }else{
            cout<<"El cliente con numero de ID "<<id_cliente_eliminar<<
                  " no existe en el archivo"<<endl<<endl;
        }
    }

}

void consultar_estado_peli() {
    ifstream archivo("movies.csv", ios::in);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl << endl;
        return;
    }

    string linea;
    string id, movie, genders, duration, director, price, release_on, rent_to, rent_on, status;
    string busqueda;
    int opcion;

    cout << "Seleccione el método de búsqueda:" << endl;
    cout << "1. Por ID" << endl;
    cout << "2. Por Nombre" << endl;
    cout << "Opción: ";
    cin >> opcion;
    cin.ignore(); // Limpia el buffer de entrada

    if (opcion == 1) {
        cout << "Ingrese el ID de la pelicula a consultar: ";
        getline(cin, busqueda);
    } else if (opcion == 2) {
        cout << "Ingrese el nombre de la pelicula a consultar: ";
        getline(cin, busqueda);
    } else {
        cout << "Opción no válida." << endl;
        return;
    }

    bool existe = false;
    getline(archivo, linea); // Saltar la línea del encabezado
    while (getline(archivo, linea)) {
        stringstream llave(linea);
        getline(llave, id, ';');
        getline(llave, movie, ';');
        getline(llave, genders, ';');
        getline(llave, duration, ';');
        getline(llave, director, ';');
        getline(llave, price, ';');
        getline(llave, release_on, ';');
        getline(llave, rent_to, ';');
        getline(llave, rent_on, ';');
        getline(llave, status, ';');

        bool coincidencia = (opcion == 1 && busqueda.compare(id) == 0) || (opcion == 2 && busqueda.compare(movie) == 0);

        if (coincidencia) {
            existe = true;
            if (status == "rentada") {
                ifstream archivo_clientes("clientes.csv");
                string nombre_cliente;
                string linea_cliente, id_cliente, nombre;
                while (getline(archivo_clientes, linea_cliente)) {
                    stringstream ss(linea_cliente);
                    getline(ss, id_cliente, ';');
                    getline(ss, nombre, ';');
                    if (rent_to == id_cliente) {
                        nombre_cliente = nombre;
                        break;
                    }
                }
                cout << "La pelicula " << movie << " ha sido rentada por " << nombre_cliente << " el dia " << rent_on << "." << endl;
            } else {
                cout << "La pelicula " << movie << " se encuentra disponible." << endl;
            }
            break;
        }
    }
    archivo.close();
    if (!existe) {
        cout << "La pelicula buscada no existe en el archivo." << endl;
    }
}

void devolver_pelicula() {
    string id_cliente, nombre_pelicula;
    cout << "Ingrese su ID de cliente: ";
    cin >> id_cliente;
    cin.ignore(); // Limpiar buffer
    cout << "Ingrese el nombre de la película a devolver: ";
    getline(cin, nombre_pelicula);

    ifstream archivo_peliculas("movies.csv");
    ofstream temp_peliculas("temp_movies.csv");
    string linea;
    bool pelicula_devuelta = false, pelicula_encontrada = false;
    while (getline(archivo_peliculas, linea)) {
        stringstream ss(linea);
        string id, movie, genders, duration, director, price, release_on, rent_to, rent_on, status;
        getline(ss, id, ';');
        getline(ss, movie, ';');
        getline(ss, genders, ';');
        getline(ss, duration, ';');
        getline(ss, director, ';');
        getline(ss, price, ';');
        getline(ss, release_on, ';');
        getline(ss, rent_to, ';');
        getline(ss, rent_on, ';');
        getline(ss, status, ';');

        if (movie == nombre_pelicula) {
            pelicula_encontrada = true;
            if (status == "rentada" && rent_to == id_cliente) {
                pelicula_devuelta = true;
                // Actualizar la información de la película a "Disponible"
                temp_peliculas << id << ';' << movie << ';' << genders << ';' << duration << ';' << director << ';' << price << ';' << release_on << ";;" << "Disponible" << '\n';
            } else {
                temp_peliculas << linea << '\n';
            }
        } else {
            temp_peliculas << linea << '\n';
        }
    }
    archivo_peliculas.close();
    temp_peliculas.close();
    remove("movies.csv");
    rename("temp_movies.csv", "movies.csv");

    if (!pelicula_encontrada) {
        cout << "Película no encontrada en el registro." << endl;
        return;
    }
    if (!pelicula_devuelta) {
        cout << "Película no está rentada por el cliente o ya ha sido devuelta." << endl;
        return;
    }

    ifstream archivo_clientes("clientes.csv");
    ofstream temp_clientes("temp_clientes.csv");
    bool cliente_actualizado = false;
    while (getline(archivo_clientes, linea)) {
        stringstream ss(linea);
        string id, nombre, peliculas_rentadas;
        getline(ss, id, ';');
        getline(ss, nombre, ';');
        getline(ss, peliculas_rentadas);

        if (id == id_cliente) {
            size_t pos = peliculas_rentadas.find(nombre_pelicula);
            if (pos != string::npos) {
                // Remover la película de la lista de películas rentadas
                peliculas_rentadas.erase(pos, nombre_pelicula.length());
                if (peliculas_rentadas[pos-1] == ',') {
                    peliculas_rentadas.erase(pos-1, 1); // Eliminar la coma adicional
                }
                cliente_actualizado = true;
            }
            temp_clientes << id << ';' << nombre << ';' << peliculas_rentadas << '\n';
        } else {
            temp_clientes << linea << '\n';
        }
    }
    archivo_clientes.close();
    temp_clientes.close();
    remove("clientes.csv");
    rename("temp_clientes.csv", "clientes.csv");

    if (cliente_actualizado) {
        cout << "Película devuelta correctamente y registro del cliente actualizado." << endl;
    } else {
        cout << "Error al actualizar el registro del cliente." << endl;
    }
}
// Función para el menú del blockbuster
void menu() {
    int opcion;

    do {
        cout << "------------------MENU-------------------" << endl;
        cout << "1. Visualizar informacion de una pelicula" << endl;
        cout << "2. Filtrar peliculas" << endl;
        cout << "3. Consultar estado de renta de una pelicula" << endl;
        cout << "4. Realizar renta de una pelicula" << endl;
        cout << "5. Agregar nuevas peliculas" << endl;
        cout << "6. Buscar cliente por ID o Nombre" << endl;
        cout << "7. Registrarse como nuevo cliente" << endl;
        cout << "8. Borrar informacion de un cliente" << endl;
        cout << "9. Borrar pelicula del sistema" << endl;
        cout << "10. Devolver pelicula rentada" << endl;
        cout << "0. Salir" << endl;

        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: visualizar_info_peli(); break;
            case 2: filtrar_peliculas(); break;
            case 3: consultar_estado_peli(); break;
            case 4: rentar_peliculas(); break;
            case 5: agregar_peliculas(); break;
            case 6: buscar_clientes(); break;
            case 7: registrar_clientes(); break;
            case 8: borrar_cliente(); break;
            case 9: borrar_peliculas(); break;
            case 10: devolver_pelicula(); break;
            case 0:{
                cout << "GRACIAS POR USAR EL PROGRAMA!" << endl;
                break;
            }
            default:
                cout << "Opcion incorrecta. Por favor ingresa una correcta." << endl;
                break;
        }
    } while (opcion != 0);
}

int main() {
    setlocale(LC_ALL, ""); //Funcion para poder ver las letras especiales, libreria <locale>
    menu();  // Llama a la función del menú
    return 0;
}
