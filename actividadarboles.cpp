//isaac mina Alomia
//Yeimi Camila lopez
#include <iostream>
#include <cstdlib>

using namespace std;

struct NodoArbol {
    int codigoRNT;
    int fechaVencimiento;
    NodoArbol* izquierda;
    NodoArbol* derecha;
};

NodoArbol* crearNodo(int codigo, int fecha) {
    NodoArbol* nuevoNodo = (NodoArbol*)malloc(sizeof(NodoArbol));
    nuevoNodo->codigoRNT = codigo;
    nuevoNodo->fechaVencimiento = fecha;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

NodoArbol* insertarNodoCodigo(NodoArbol* raiz, int codigo, int fecha) {
    if (raiz == NULL) {
        return crearNodo(codigo, fecha);
    }
    if (codigo < raiz->codigoRNT) {
        raiz->izquierda = insertarNodoCodigo(raiz->izquierda, codigo, fecha);
    } else {
        raiz->derecha = insertarNodoCodigo(raiz->derecha, codigo, fecha);
    }
    return raiz;
}

NodoArbol* insertarNodoFecha(NodoArbol* raiz, int codigo, int fecha) {
    if (raiz == NULL) {
        return crearNodo(codigo, fecha);
    }
    if (fecha < raiz->fechaVencimiento) {
        raiz->izquierda = insertarNodoFecha(raiz->izquierda, codigo, fecha);
    } else {
        raiz->derecha = insertarNodoFecha(raiz->derecha, codigo, fecha);
    }
    return raiz;
}

void insertarNodoPrincipalCodigo(NodoArbol*& raiz) {
    int codigo, fecha;
    cout << "Ingrese el codigo RNT del nodo: ";
    cin >> codigo;
    cout << "Ingrese la fecha de vencimiento del RNT del nodo (AAAAMMDD): ";
    cin >> fecha;
    raiz = insertarNodoCodigo(raiz, codigo, fecha);
    cout << "Nodo insertado correctamente." << endl;
}

void insertarNodoPrincipalFecha(NodoArbol*& raiz) {
    int codigo, fecha;
    cout << "Ingrese el codigo RNT del nodo: ";
    cin >> codigo;
    cout << "Ingrese la fecha de vencimiento del RNT del nodo (AAAAMMDD): ";
    cin >> fecha;
    raiz = insertarNodoFecha(raiz, codigo, fecha);
    cout << "Nodo insertado correctamente." << endl;
}

void preorden(NodoArbol* raiz) {
    if (raiz != NULL) {
        cout << "Codigo RNT: " << raiz->codigoRNT << ", Fecha de vencimiento: " << raiz->fechaVencimiento << endl;
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void inorden(NodoArbol* raiz) {
    if (raiz != NULL) {
        inorden(raiz->izquierda);
        cout << "Codigo RNT: " << raiz->codigoRNT << ", Fecha de vencimiento: " << raiz->fechaVencimiento << endl;
        inorden(raiz->derecha);
    }
}

void posorden(NodoArbol* raiz) {
    if (raiz != NULL) {
        posorden(raiz->izquierda);
        posorden(raiz->derecha);
        cout << "Codigo RNT: " << raiz->codigoRNT << ", Fecha de vencimiento: " << raiz->fechaVencimiento << endl;
    }
}

NodoArbol* eliminarNodoCodigo(NodoArbol* raiz, int codigo) {
    if (raiz == NULL) {
        return raiz;
    }
    if (codigo < raiz->codigoRNT) {
        raiz->izquierda = eliminarNodoCodigo(raiz->izquierda, codigo);
    } else if (codigo > raiz->codigoRNT) {
        raiz->derecha = eliminarNodoCodigo(raiz->derecha, codigo);
    } else {
        if (raiz->izquierda == NULL) {
            NodoArbol* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            NodoArbol* temp = raiz->izquierda;
            free(raiz);
            return temp;
        }
        NodoArbol* temp = raiz->derecha;
        while (temp->izquierda != NULL) {
            temp = temp->izquierda;
        }
        raiz->codigoRNT = temp->codigoRNT;
        raiz->fechaVencimiento = temp->fechaVencimiento;
        raiz->derecha = eliminarNodoCodigo(raiz->derecha, temp->codigoRNT);
    }
    return raiz;
}

NodoArbol* eliminarNodoFecha(NodoArbol* raiz, int fecha) {
    if (raiz == NULL) {
        return raiz;
    }
    if (fecha < raiz->fechaVencimiento) {
        raiz->izquierda = eliminarNodoFecha(raiz->izquierda, fecha);
    } else if (fecha > raiz->fechaVencimiento) {
        raiz->derecha = eliminarNodoFecha(raiz->derecha, fecha);
    } else {
        if (raiz->izquierda == NULL) {
            NodoArbol* temp = raiz->derecha;
            free(raiz);
            return temp;
        } else if (raiz->derecha == NULL) {
            NodoArbol* temp = raiz->izquierda;
            free(raiz);
            return temp;
        }
        NodoArbol* temp = raiz->derecha;
        while (temp->izquierda != NULL) {
            temp = temp->izquierda;
        }
        raiz->codigoRNT = temp->codigoRNT;
        raiz->fechaVencimiento = temp->fechaVencimiento;
        raiz->derecha = eliminarNodoFecha(raiz->derecha, temp->fechaVencimiento);
    }
    return raiz;
}

void liberarArbol(NodoArbol* raiz) {
    if (raiz != NULL) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        free(raiz);
    }
}

int main() {
    NodoArbol* raizPrincipalCodigo = NULL;
    NodoArbol* raizPrincipalFecha = NULL;

    int opcion;
    do {
        cout << "\n1. Insertar nodo por codigo" << endl;
        cout << "2. Insertar nodo por fecha" << endl;
        cout << "3. Recorrer en preorden (por codigo)" << endl;
        cout << "4. Recorrer en inorden (por codigo)" << endl;
        cout << "5. Recorrer en posorden (por codigo)" << endl;
        cout << "6. Recorrer en preorden (por fecha)" << endl;
        cout << "7. Recorrer en inorden (por fecha)" << endl;
        cout << "8. Recorrer en posorden (por fecha)" << endl;
        cout << "9. Eliminar nodo por codigo" << endl;
        cout << "10. Eliminar nodo por fecha" << endl;
        cout << "11. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                insertarNodoPrincipalCodigo(raizPrincipalCodigo);
                break;
            case 2:
                insertarNodoPrincipalFecha(raizPrincipalFecha);
                break;
            case 3:
                cout << "Recorrido preorden del arbol principal (por codigo):" << endl;
                preorden(raizPrincipalCodigo);
                break;
            case 4:
                cout << "Recorrido inorden del arbol principal (por codigo):" << endl;
                inorden(raizPrincipalCodigo);
                break;
            case 5:
                cout << "Recorrido posorden del arbol principal (por codigo):" << endl;
                posorden(raizPrincipalCodigo);
                break;
            case 6:
                cout << "Recorrido preorden del arbol principal (por fecha):" << endl;
                preorden(raizPrincipalFecha);
                break;
            case 7:
                cout << "Recorrido inorden del arbol principal (por fecha):" << endl;
                inorden(raizPrincipalFecha);
                break;
            case 8:
                cout << "Recorrido posorden del arbol principal (por fecha):" << endl;
                posorden(raizPrincipalFecha);
                break;
            case 9:
                int codigoEliminar;
                cout << "Ingrese el codigo RNT del nodo a eliminar: ";
                cin >> codigoEliminar;
                raizPrincipalCodigo = eliminarNodoCodigo(raizPrincipalCodigo, codigoEliminar);
                cout << "Nodo eliminado correctamente." << endl;
                break;
            case 10:
                int fechaEliminar;
                cout << "Ingrese la fecha de vencimiento del nodo a eliminar (AAAAMMDD): ";
                cin >> fechaEliminar;
                raizPrincipalFecha = eliminarNodoFecha(raizPrincipalFecha, fechaEliminar);
                cout << "Nodo eliminado correctamente." << endl;
                break;
            case 11:
                cout << "Saliendo del programa..." << endl;
                liberarArbol(raizPrincipalCodigo);
                liberarArbol(raizPrincipalFecha);
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 11);

    return 0;
}
