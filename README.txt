Ce projet est à remettre au goût du jour:
Il faudrait récupérer ce qu'il y avait de bon dans Skull engine (Core/Window/Graphics).
Puis refactoriser Graphics: GraphicsDevice (un pour chaque API) et GraphicsRenderer séparés.
Le GraphicsRenderer serait alors une sorte de glue rendant compatible les différents Devices,
et capable d'optimiser le rendu, faire des effets etc... Un truc plus haut-niveau que les simples GraphicsDevice
qui eux ne sont que des abstractions des APIs de rendus.

Après il faudrait améliorer la documentation, faire des exemples plus fournis.
