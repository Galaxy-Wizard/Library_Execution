# Library_Execution
"Library Execution" implements function execution in libraries.

Executing functions of following type

typedef PWCHAR(FAR WINAPI *FAR_FUNCTION_POINTER)(PWCHAR);

Example.

Parametes is a pointer to string of WCHAR terminating by zero symbol.
Result is a pointer to string of WCHAR terminating by zero symbol.

Main Application "Library_Execution" executes function "Main"
of "Dynamic_Extended_Library_Applications" Library.

Function "Main" of "Dynamic_Extended_Library_Applications" Library
shows dialog, that allows to select "Dynamic_Extended_Library_Applications" Library
Applications to be executed.


General overview.

Main Application "Library_Execution" executes function "Main"
of selected our library.
Every our type library has function "Main".
This function "Main" shows applications of library
(exported functions).
Function "Main" can execute each our type library application
(exported function).


"Main" function of our library is similar to 
Application "Library_Execution" Main dialog.

You are welcome to use "Dynamic_Extended_Library_Applications"
template to create our type libraries.

