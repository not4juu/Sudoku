# Rozwiązywanie sudoku na podstawie zdjęć z kamery

Projekt realizowany w ramach przedmiotu Analiza i Przetwarzanie obrazów, AGH 2016/2017.

### Autor

 - Sebastian Kałużny

 Projekt
----
1. Znajdowanie w obrazie głównej planszy sudoku
2. Przygotowanie obrazu pod OCR -> detekcja i usuniecie lini z obrazu aby pozostały same cyfry
3. Wywołanie algorytmu OCR dla otrzymanego obrazu
4. Detekcja położenie wykrytych cyfr względem planszy sudoku, zapis do tablicy dwuwymiarowej oraz wykrycie poszczególnych pul sudoku
5. Wywołanie algorytmu rozwiązującego sudoku
6. Zapisanie wyników na główny obraz z uwzględnieniem proporcji obrazu


Dodatkow została stworzona opcja DEBUG -> nalezy odkomentowac ja w pliku SudokuConf.h otrzymamy dzięki temu obrazy z poszczególnych etapów obroki oraz w konsoli znajda sie dodatkowe logi.
