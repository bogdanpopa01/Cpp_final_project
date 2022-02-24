# Descriere proiect

Intrucat sunt pasionat de gamedev, am ales ca tema proiectului meu sa fie indreptata in aceasta directie. In proiect se afla o clasa de baza `Monster` avand ca atribute: nume,
hp (_Health Points_), nrAbilitati si un vector dinamic in care sunt stocate daunele pe care aceste abilitati le provoaca. Din aceasta clasa sunt derivate alte trei: Zombie, 
giantSpider si Skeleton. Skeleton-ul la randul sau are doi copii: WaterSkeleton si FireSkeleton. Exista si clasa `CompunereDeMonsters`, iar un obiect de acest tip va stoca
intr-un vector dinamic mai multe obiecte de tipul `Monster`. \
Toate aceste clase mostenesc in mod public clasa `InterfataMonster` pentru a implementa functia `experientaNecesara()`, functie care va arata cate _experience points_ 
va dropa fiecare tip de monstru. 

 In acest proiect se vor regasi urmatoarele:
  - utilizarea corecta a constructorului de copiere si a operatorului egal pentru a se evita shallow-copy-ul
  - utilizarea unei clase abstracte si a unei interfete
  - supraincarcarea tuturor operatorilor 
  - folosirea unei clase de tip compunere
  - utilizarea de settari si gettari
  - folosirea exceptiilor custom si prinderea acestora in blocuri de tip try-catch
  - serializare/deserializare
  - utilizarea STL-urilor si a functiilor template
  - demonstrarea conceptelor de early si late-binding
  - demonstrarea conceptului de polimorfism folosind o clasa abstracta
