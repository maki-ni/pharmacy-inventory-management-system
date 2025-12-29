# Pharmacy-Inventory-Management-System

System that will register patients, search drugs from given database, delete expired drugs, register new drugs into inventory, show number of abvailable drugs of a specific catagory and show total number of drugs in the database and patients registered.

# How to run the file

To run the file on your local terminal type ./build.ps1 and it will automaticaly run it (change the code inside ./build.ps1 accordingly -->
g++ main.cpp modules/PatientQueue.cpp modules/DrugBST.cpp -o app.exe;
Write-Host "Build Complete! Running ..."
.\app.exe;
)

For linux systems, simply run ./build.sh!

