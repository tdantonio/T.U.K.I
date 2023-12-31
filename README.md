# <h1 align="center"> Trabajo Práctico de Sistemas Operativos - UTN FRBA </h1>

## "T.U.K.I - The Ultimate Kernel Implementation"

[Enunciado del TP](https://github.com/tdantonio/T.U.K.I/blob/main/docs/Enunciado%20T.U.K.I%20-%20v1.1.pdf)

[Documento de pruebas del TP](https://github.com/tdantonio/T.U.K.I/blob/main/docs/1C2023%20-%20TUKI%20-%20Pruebas.pdf)

* Fecha de realización: Abril 2023 -> Julio 2023

## Deploy :electric_plug:
En una terminal bash:
 - git clone https://github.com/tdantonio/T.U.K.I.git
 - cd T.U.K.I/
 - chmod u+x scripts/dependencies.sh
 - . ./scripts/dependencies.sh
 - ./scripts/set_ips.sh <kernel_ip> <cpu_ip> <fs_ip> <mem_ip> <sup>1</sup>
 
Ejecucion de cualquier modulo <sup>2</sup>
  - ./Debug/<modulo> <config_abs_path> <sup>3</sup>

## Construido con 🛠️

* [Oracle VM VirtualBox](https://www.virtualbox.org/wiki/Downloads) - Virtual Machine
* [Eclipse](https://www.eclipse.org/downloads/)  - IDE usado incluído en la VM
* [Xubuntu - 64 bit](https://drive.google.com/drive/folders/1ASZjI4HsAKDZNgNJ-owhZA2GAJ8Rsqjr) - Versión para desarrollo con entorno gráfico liviano (XFCE).
* [Ubuntu Server (64-bit)](https://drive.google.com/drive/folders/1Pn1SveTGkEVfcc7dYAr1Wc10ftEe8E0J) - Versión de pruebas, sin entorno gráfico. En esta VM se evaluó el TP.
* [C](https://github.com/search?q=repo%3Atdantonio%2FT.U.K.I++language%3AC&type=code) - Lenguaje utilizado

## Autores ✒️

* **Tomás D'Antonio** - Team: *Kernel/CPU/File System/Memoria* - [tdantonio](https://github.com/tdantonio)
* **Federico Moccia** - Team: *CPU/File System* - [moccia01](https://github.com/moccia01)
* **Lucas Boldrini** - Team: *CPU/File System* - [LucasBoldrini007](https://github.com/LucasBoldrini007)
* **Nahuel Gimenez** - Team: *Memoria* - [NahuGim](https://github.com/NahuGim)
* **Bautista Rodriguez** - Team: *Memoria* - [BauRodriguez](https://github.com/BauRodriguez)

También podés mirar el gráfico de [contribuciones](https://github.com/tdantonio/T.U.K.I/graphs/contributors)

## Links útiles 🎁

* [La caja de UTN](https://lacajadeutn.blogspot.com/)
* [Blog UTNSO](https://www.utnso.com.ar/)
* [Foro de consultas](https://github.com/sisoputnfrba/foro)

### Notas :clipboard:
<p><sup>1</sup> El proyecto esta preparado para correr en un entorno distribuido, aca es donde entra en juego el script set_ips.sh que es el encargado de bindear, a los archivos de configuracion, la ip de donde se esta ejecutando cada modulo.</p>
<p><sup>2</sup> Hay algunos modulos que dependen de otros, por lo que existe un orden correcto de ejecución. Para más detalle se recomienda leer el enunciado.</p>
<p><sup>3</sup> En el caso del modulo consola tambien se deberia recibir por parámetro la ruta absoluta al archivo de instrucciones a ejecutar</p>
