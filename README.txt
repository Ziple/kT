Ce projet est � remettre au go�t du jour:
Il faudrait r�cup�rer ce qu'il y avait de bon dans Skull engine (Core/Window/Graphics).
Puis refactoriser Graphics: GraphicsDevice (un pour chaque API) et GraphicsRenderer s�par�s.
Le GraphicsRenderer serait alors une sorte de glue rendant compatible les diff�rents Devices,
et capable d'optimiser le rendu, faire des effets etc... Un truc plus haut-niveau que les simples GraphicsDevice
qui eux ne sont que des abstractions des APIs de rendus.

Apr�s il faudrait am�liorer la documentation, faire des exemples plus fournis.
