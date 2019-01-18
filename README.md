# graZaliczenie
Plik wykonywalny o nazwie grazaliczenie był kompilowany pod system Ubuntu 18.10. W celu uruchomienia gry pod starszą wersją Ubuntu bądz inną dystrybucją linuksa może być potrzebne ponowne skompilowanie programu. W tym celu potrzebne jest:
 - Zainstalowanie kompilatora g++ (komenda pod ubuntu 'sudo apt install g++') 
 - Zainstalowanie biblioteki ncurses (komenda 'sudo apt install libncurses-dev'). 
 
Aby nie trzeba było ręcznie wpisywać komendy w plikach znajduje się plik compile.sh zawierający gotową komendę. Aby go uruchomić należy najpierw dać mu uprawnienia do uruchomienia komendą 'chmod +x compile.sh'. A następnie uruchomić komendą './compile.sh'.

Po pomyślnym zakończeniu kompilacji grę uruchomić można komendą './grazaliczenie'
! W razie gdyby system nie chciał jej uruchomić może być konieczne użycie komendy 'chmod +x grazaliczenie'. Jednak nie powinno być to konieczne.

Na stan aktualny gra zawiera 2 poziomy jednak w celu dodania nowego należy w pliku mapy/mapy.dat dodać ścieżkę do pliku z nowym poziomem, oraz stworzyć poziom o takiej nazwie o wymiarach takich jak poziomy już stworzone.

! W chwilach wolnych postaram się dodać więcej poziomów i opcjonalnie dodać zapis stanu gry.

Życzę miłej zabawy z grą.
