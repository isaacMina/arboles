#include <iostream>
#include <cstdlib>
using namespace std;

struct Empresa {
    int RNT;
    string nombre;
    int ano;
    int mes;
    int dia;
    Empresa* izq;
    Empresa* der;
};

Empresa *raiz, *raiz2, *aux, *aux2, *auxC, *auxF, *aux2C, *aux2F;

int posicionar(){
     if(aux->RNT < aux2->RNT){
             if(aux2->izq!=NULL){
             aux2 = aux2->izq;
             posicionar();
            }
           else
            aux2->izq = aux;
        }
       else if(aux->RNT > aux2->RNT){
          if(aux2->der!=NULL){
              aux2 = aux2->der;
             posicionar();
            }
          else{
             aux2->der = aux;
            }
        }
      return 0;
}

int posicionarFechaVencimiento() {
    if (aux->ano < aux2->ano) {
        if (aux2->izq != NULL) {
            aux2 = aux2->izq;
            posicionarFechaVencimiento();
        } else {
            aux2->izq = aux;
        }
    } else if (aux->ano > aux2->ano) {
        if (aux2->der != NULL) {
            aux2 = aux2->der;
            posicionarFechaVencimiento();
        } else {
            aux2->der = aux;
        }
    } else {
        // Si los años son iguales, se compara por mes
        if (aux->mes < aux2->mes) {
            if (aux2->izq != NULL) {
                aux2 = aux2->izq;
                posicionarFechaVencimiento();
            } else {
                aux2->izq = aux;
            }
        } else if (aux->mes > aux2->mes) {
            if (aux2->der != NULL) {
                aux2 = aux2->der;
                posicionarFechaVencimiento();
            } else {
                aux2->der = aux;
            }
        } else {
            // Si los meses también son iguales, se compara por día
            if (aux->dia < aux2->dia) {
                if (aux2->izq != NULL) {
                    aux2 = aux2->izq;
                    posicionarFechaVencimiento();
                } else {
                    aux2->izq = aux;
                }
            } else if (aux->dia > aux2->dia) {
                if (aux2->der != NULL) {
                    aux2 = aux2->der;
                    posicionarFechaVencimiento();
                } else {
                    aux2->der = aux;
                }
            } else {
                // Si las fechas son idénticas, se decide cómo manejarlo (por ejemplo, ignorar o agregar a una lista)
            }
        }
    }
    return 0;
}

int registrarEmpresa(){
    aux = (Empresa*) malloc (sizeof(Empresa));
    cout<<"Ingresa Código RNT: ";
    cin>> aux->RNT; 
    cout << "Ingresa Nombre: ";
    cin >> aux->nombre;
    cout << "Ingresa Año: ";
    cin >> aux->ano;
    cout << "Ingresa Mes: ";
    cin >> aux->mes;
    cout << "Ingresa Día: ";
    cin >> aux->dia;
    aux->izq = aux->der =  nullptr;
    	     
    if(raiz==NULL){
	    raiz = aux;
	    aux = NULL;
	    free(aux);
	}

    if (raiz2 == NULL) {
        raiz2 = aux;
    } else {
        aux2 = raiz2;
        posicionarFechaVencimiento();
    }

    return 0;
}

int ubicar(Empresa *aux4, int aguja){ //identificar el elemento
    if(aux4->RNT == aguja){
        auxC = aux4;
        return 1;
    }  
    else {
        if(aux4->izq!=NULL){
            ubicar(aux4->izq, aguja);
        }
        if(aux4->der!=NULL){
            ubicar(aux4->der, aguja);
        }
    }
    return 0;
}

int ubicar2(Empresa *aux3, int aguja2){ //identificar el elemento
    if(aux3->RNT == aguja2){
        auxF = aux3;
        return 1;
    }  
    else {
        if(aux3->izq!=NULL){
            ubicar2(aux3->izq, aguja2);
        }
        if(aux3->der!=NULL){
            ubicar2(aux3->der, aguja2);
        }
    }
    return 0;
}

int ubicarpadrecodigo(Empresa *padre){
    if((padre->izq!=NULL)&&(padre->izq!=auxC)){
        ubicarpadrecodigo(padre->izq);
    }
    if(padre->izq == auxC){
        aux2C = padre;
    }
    if((padre->der!=NULL)&&(padre->der!=auxC)){
        ubicarpadrecodigo(padre->der);
    }
    if(padre->der == auxC){
        aux2C = padre;
    }
    return 0;	
} 

int ubicarpadrefecha(Empresa *padre2){
    if((padre2->izq!=NULL)&&(padre2->izq!=auxF)){
        ubicarpadrefecha(padre2->izq);
    }
    if(padre2->izq == auxF){
        aux2F = padre2;
    }
    if((padre2->der!=NULL)&&(padre2->der!=auxF)){
        ubicarpadrefecha(padre2->der);
    }
    if(padre2->der == auxF){
        aux2F = padre2;
    }
    return 0;	
} 

int casoUnocodigo(){
    if(auxC!=raiz){
        ubicarpadrecodigo(raiz);	
    }
    if(aux2C->izq == auxC){
        aux2C->izq = NULL;
    }
    if(aux2C->der == auxC){
        aux2C->der = NULL;
    }
    free(auxC);
    return 0;
}

int casoUnofecha(){
    if(auxF!=raiz2){
        ubicarpadrefecha(raiz2);	
    }
    if(aux2F->izq == auxF){
        aux2F->izq = NULL;
    }
    if(aux2F->der == auxF){
        aux2F->der = NULL;
    }
    free(auxF);
    return 0;
}

int casoDoscodigo(){
    if(auxC!=raiz){
        ubicarpadrecodigo(raiz);	
    }
    if(aux2C->izq == auxC){
        if((auxC->izq!=NULL)&&(auxC->der!=NULL)){
            aux2C->izq = auxC->der;
            posicionar();
        }
        if(auxC->izq!=NULL){
            aux2C->izq = auxC->izq;
        }
        if(auxC->der!=NULL){
            aux2C->izq = auxC->der;
        }
    }
    if(aux2C->der == auxC){
        if((auxC->izq!=NULL)&&(auxC->der!=NULL)){
            aux2C->der = auxC->der;
            posicionar();
        }
        if(auxC->izq!=NULL){
            aux2C->der = auxC->izq;
        }
        if(auxC->der!=NULL){
            aux2C->der = auxC->der;
        }
    }
    free(auxC);
    return 0;
}

int casoDosfecha(){
    if(auxF!=raiz2){
        ubicarpadrefecha(raiz2);	
    }
    if(aux2F->izq == auxF){
        if((auxF->izq!=NULL)&&(auxF->der!=NULL)){
            aux2F->izq = auxF->der;
            posicionarFechaVencimiento();
        }
        if(auxF->izq!=NULL){
            aux2F->izq = auxF->izq;
        }
        if(auxF->der!=NULL){
            aux2F->izq = auxF->der;
        }
    }
    if(aux2F->der == auxF){
        if((auxF->izq!=NULL)&&(auxF->der!=NULL)){
            aux2F->der = auxF->der;
            posicionarFechaVencimiento();
        }
        if(auxF->izq!=NULL){
            aux2F->der = auxF->izq;
        }
        if(auxF->der!=NULL){
            aux2F->der = auxF->der;
        }
    }
    free(auxF);
    return 0;
}

int eliminarEmpresaCodigo(){
    int aguja;
    cout<<"Ingrese el Código RNT de la empresa a eliminar: ";
    cin>>aguja;
    auxC = NULL;
    ubicar(raiz, aguja);
    if(auxC!=NULL){
        if((auxC->izq==NULL)&&(auxC->der==NULL)){
            casoUnocodigo();
        }
        if((auxC->izq!=NULL)&&(auxC->der!=NULL)){
            casoDoscodigo();
        }
    }
    else{
        cout<<"No se encontró la empresa con ese Código RNT."<<endl;
    }
    return 0;
}

int eliminarEmpresaFecha(){
    int aguja2;
    cout<<"Ingrese el Código RNT de la empresa a eliminar: ";
    cin>>aguja2;
    auxF = NULL;
    ubicar2(raiz2, aguja2);
    if(auxF!=NULL){
        if((auxF->izq==NULL)&&(auxF->der==NULL)){
            casoUnofecha();
        }
        if((auxF->izq!=NULL)&&(auxF->der!=NULL)){
            casoDosfecha();
        }
    }
    else{
        cout<<"No se encontró la empresa con ese Código RNT."<<endl;
    }
    return 0;
}

int preorden(Empresa *recursive){
      cout<<"RNT: "<<recursive->RNT<<endl;
      cout<<"Nombre: "<<recursive->nombre<<endl;
      cout<<"Fecha: "<<recursive->ano<<"/"<<recursive->mes<<"/"<<recursive->dia<<endl;
      cout<<"\n";
      cout<<"----------------------------------------------------------"<<endl;
      cout<<"\n";
      if(recursive->izq!=NULL){
         preorden(recursive->izq);
        }
      if(recursive->der!=NULL){
         preorden(recursive->der);
        }
     return 0;
}

int inOrden(Empresa *recursive){
	  if(recursive->izq!=NULL){
         inOrden(recursive->izq);
        }
      cout<<"RNT: "<<recursive->RNT<<endl;
      cout<<"Nombre: "<<recursive->nombre<<endl;
      cout<<"Fecha: "<<recursive->ano<<"/"<<recursive->mes<<"/"<<recursive->dia<<endl;
      cout<<"\n";
      cout<<"----------------------------------------------------------"<<endl;
      cout<<"\n";
     if(recursive->der!=NULL){
          inOrden(recursive->der);
        }
     return 0;
}

int postorden(Empresa *recursive){
      if(recursive->izq!=NULL){
         postorden(recursive->izq);
        }
      if(recursive->der!=NULL){
         postorden(recursive->der);
        }
      cout<<"RNT: "<<recursive->RNT<<endl;
      cout<<"Nombre: "<<recursive->nombre<<endl;
      cout<<"Fecha: "<<recursive->ano<<"/"<<recursive->mes<<"/"<<recursive->dia<<endl;
      cout<<"\n";
      cout<<"----------------------------------------------------------"<<endl;
      cout<<"\n";
     return 0;
}

int preordenFecha(Empresa *recursive){
      cout<<"Fecha: "<<recursive->ano<<"/"<<recursive->mes<<"/"<<recursive->dia<<endl;
      cout<<"\n";
      cout<<"----------------------------------------------------------"<<endl;
      cout<<"\n";
      if(recursive->izq!=NULL){
         preordenFecha(recursive->izq);
        }
      if(recursive->der!=NULL){
         preordenFecha(recursive->der);
        }
     return 0;
}

int inOrdenFecha(Empresa *recursive){
	  if(recursive->izq!=NULL){
         inOrdenFecha(recursive->izq);
        }
      cout<<"Fecha: "<<recursive->ano<<"/"<<recursive->mes<<"/"<<recursive->dia<<endl;
      cout<<"\n";
      cout<<"----------------------------------------------------------"<<endl;
      cout<<"\n";
     if(recursive->der!=NULL){
          inOrdenFecha(recursive->der);
        }
     return 0;
}

int postordenFecha(Empresa *recursive){
      if(recursive->izq!=NULL){
         postordenFecha(recursive->izq);
        }
      if(recursive->der!=NULL){
         postordenFecha(recursive->der);
        }
      cout<<"Fecha: "<<recursive->ano<<"/"<<recursive->mes<<"/"<<recursive->dia<<endl;
      cout<<"\n";
      cout<<"----------------------------------------------------------"<<endl;
      cout<<"\n";
     return 0;
}

int menu(){
    int opc;
    do{
        cout<<"1. Registrar empresa"<<endl;
        cout<<"2. Eliminar empresa por código"<<endl;
        cout<<"3. Eliminar empresa por fecha de vencimiento"<<endl;
        cout<<"4. Mostrar empresas (preorden)"<<endl;
        cout<<"5. Mostrar empresas (inorden)"<<endl;
        cout<<"6. Mostrar empresas (postorden)"<<endl;
        cout<<"7. Mostrar empresas por fecha de vencimiento (preorden)"<<endl;
        cout<<"8. Mostrar empresas por fecha de vencimiento (inorden)"<<endl;
        cout<<"9. Mostrar empresas por fecha de vencimiento (postorden)"<<endl;
        cout<<"10. Salir"<<endl;
        cout<<"Opción: ";
        cin>>opc;
        switch(opc){
            case 1:
                registrarEmpresa();
                break;
            case 2:
                eliminarEmpresaCodigo();
                break;
            case 3:
                eliminarEmpresaFecha();
                break;
            case 4:
                cout<<"\n";
                cout<<"Empresas (Preorden):"<<endl;
                cout<<"\n";
                preorden(raiz);
                break;
            case 5:
                cout<<"\n";
                cout<<"Empresas (Inorden):"<<endl;
                cout<<"\n";
                inOrden(raiz);
                break;
            case 6:
                cout<<"\n";
                cout<<"Empresas (Postorden):"<<endl;
                cout<<"\n";
                postorden(raiz);
                break;
            case 7:
                cout<<"\n";
                cout<<"Empresas por Fecha de Vencimiento (Preorden):"<<endl;
                cout<<"\n";
                preordenFecha(raiz2);
                break;
            case 8:
                cout<<"\n";
                cout<<"Empresas por Fecha de Vencimiento (Inorden):"<<endl;
                cout<<"\n";
                inOrdenFecha(raiz2);
                break;
            case 9:
                cout<<"\n";
                cout<<"Empresas por Fecha de Vencimiento (Postorden):"<<endl;
                cout<<"\n";
                postordenFecha(raiz2);
                break;
            case 10:
                exit(0);
                break;
            default:
                cout<<"Opción no válida. Intente de nuevo."<<endl;
                break;
        }
    }while(opc!=10);
    return 0;
}

int main(){
    raiz = raiz2 = aux = aux2 = NULL;
    menu();
    return 0;
}
