Kedves Zsolt,

A megfelelő működéshez a "resources" mappát az általad fordított .exe(vagy ami lesz belőle) mellé kell bemásolnod.
- Jelenleg lehet egymás ellen lovagokat küldeni( tab és space billentyűvel ).
- A lovagok harcolnak ha közel érnek egymáshoz.
- A lovagok nem haladnak/csúzsnak egymásba, az elötte lévőt nem előzi meg.
- A lovagok pályája a háttérhez van igazítva.
- Van egy eseményvezérlő, ami billentyű/timer/exit eseményeket kezel. (event_handler.h/.c)
- Van egy játékmotor, ami tárolja és az események hatására változtatja a játék állapotát. (game_data.h/.c)
- Van egy gui is külön a megjelenítésre.(gui.h/.c)

Kell még:
- Játék vége.
- Ágyú mozgatás, lövedék mozgás és találat regisztráció.
- Gazdaság és egyéb fejlesztések.
- Lovagoknak animáció. (képek már vannak)

Üdv,
Somorjai Balázs
