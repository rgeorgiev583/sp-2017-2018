# Команден интерпретатор с поддръжка за пренасочване на стандартния вход/изход и канали

Да се разшири функционалността на командния интерпретатор от по-миналото упражнение, така че да поддържа:

1. Kанали между два процеса (със синтаксиса на `bash`).

   *Например:* `who | wc -l`

2. Пренасочване на стандартния вход/изход (със синтаксиса на `bash`).

   *Например:* `tr ab cd < foo > bar`

3. Подаване на файл(ове), съдържащ(и) списък с команди (т.е. нещо като *shell script*-ове) като аргументи на програмата.  Ако е подаден поне един аргумент на интерпретатора, вместо да се стартира в интерактивен режим, той трябва да изпълни командите във всеки от подадените файлове в дадената последователност.