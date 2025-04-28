1) Создали **enum class ``DrinkingType``** с методами выпивания вина
2) Создали **class ``DrinkingStrategy``** и его наследников: методы выпивания ``HalfDrinkingStrategy``, ``FullDrinkingStrategy``, ``EatGlassStrategy``
3) В ``DrinkingStrategy`` создали метод ``Drink``
4) Разработали фабричный метод для создания экземпляров классов стратегий ``CreateDrinkingStrategy``
5) В базовом классе ``Wine`` создали метод ``DrinkUsingStrategy``, проверяющий тип стратегии на заполненность и при положительном исходе вызывающий метод ``Drink`` с использованием выбранной стратегии
6) Создали абстрактные методы ``OutputSpecificCharacteristics`` и ``AdditionalInfo`` для унификации структуры в подклассах
7) Создали метод ``Drink`` для возможности напрямую вызывать ``DrinkUsingStrategy`` у наследников ``Wine``
8) Добавили метод ``SetDrinkingType`` для передачи типа стратегии напрямую в базовый
9) Добавили метод ``WineInfo`` для уменьшения количества дублируемого кода
10) В каждом подклассе добавили определение типа стратегии выпивания ``SetDrinkingType(CreateDrinkingStrategy(DrinkingType::type))``
11) Создали метод ``DrinkAllWine`` для вывода метода ``Drink``
