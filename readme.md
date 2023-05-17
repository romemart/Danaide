
Enunciado:
Tenemos un archivo (adjunto al mail) en formato json que contiene información de sensores. 
La información está dispuesta en un array de objetos que contienen los datos de cada sensor 
con el siguiente formato: 
{ "index": 0, "id": "f4b5b928-949b-4d4a-a13b-a718a0507e3f", "isActive": true, "zone": "Z01", "value": "17999.31" }
Se debe construir una aplicación escrita en C++ que lea el archivo json y lo procese.

El programa debe generar un archivo json que contenga la siguiente información:
- Id del sensor que sensó el mayor valor.
- El valor medio.
- El valor medio por zona.
- Cantidad de de sensores activos por zona.

El programa debe generar un archivo con los mismos datos del archivo de entrada:
- El formato de salida del archivo debe ser seleccionable.
- Los formatos disponibles deben ser CSV o XML.
- Se pueden seleccionar uno o ambos formatos a la vez.
- El programa debe poder extenderse para soportar nuevos formatos.
- Se debe poder especificar el path de cada archivo de salida, por lo tanto cada archivo puede escribirse en diferentes dispositivos.
- En el caso de escribir los archivos en diferentes dispositivos, la velocidad de escritura de un archivo no debe afectar a los demás.
- Los archivos de salida se deben generar de manera concurrente con la lectura del archivo de entrada y evitar, de ser posible, tener todo el archivo en memoria.

Para hacer el proyecto se debe utilizar visual studio.
La entrega debe hacerse en un repositorio de github.


Compilar como proyecto multifile

se compilo usando herramienta MSVC

se edito en VSCODE

el resultado despliega hasta 3 archivos:

fileJSON.json : conteniendo la informacion pedida

fileXML.xml   : cambio de formato de sensores.json con ubicacion seteable

fileCSV.csv   : cambio de formato de sensores.json con ubicacion seteable

ejecutar el proceso main.cpp y seguir los pasos del menu
en caso de compilacion exitosa deberia mostrar un menu por terminal:

```powershell
Opening the input JSON file successfully.
The file "fileJSON.json" was created successfully.


To change the format to JSON input file type:
1 - To output in XML format
2 - To output in CSV format
ANY To output both of them formats

Type: 0

Choose the path for the file "fileXML.xml"
Example: ./folderxml/ or ./ or ../

Type: ./folderxml/
Find the file in:./folderxml/fileXML.xml

Choose the path for the file "fileCSV.csv"
Example: ./foldercsv/ or ./ or ../

Type: ./foldercsv/
Find the file in:./foldercsv/fileCSV.csv

Press any key to continue . . .
```