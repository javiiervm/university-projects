using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    /// <summary>
    /// Main game class that controls the game loop and manages game events.
    /// </summary>
    internal class Game
    {
        /// <summary>
        /// Boolean flag to determine if the game has ended.
        /// </summary>
        bool finPartida;

        /// <summary>
        /// Main game loop. Continues until the player quits or all ships are sunk.
        /// </summary>
        void gameLoop()
        {
            string userInput;

            // Create ships with predefined positions and orientations
            Barco barco1 = new Barco("THOR", 1, 'h', new Coordenada(0, 0));
            Barco barco2 = new Barco("LOKI", 2, 'v', new Coordenada(1, 2));
            Barco barco3 = new Barco("MAYA", 3, 'h', new Coordenada(3, 1));

            // Initialize the game board with the created ships
            Tablero tablero = new Tablero(4, new List<Barco> { barco1, barco2, barco3 });
            tablero.eventoFinPartida += cuandoEventoFinDePartida;

            // The loop will end if the user presses 'S' or if Tablero raises the event eventoFinPartida
            while (!finPartida)
            {
                Console.WriteLine("Introduce la coordenada a la que disparar FILA,COLUMNA ('S' para Salir):");
                userInput = Console.ReadLine();

                if (userInput == "S" || userInput == "s")
                {
                    finPartida = true;
                }
                else
                {
                    // Validate user input format (FILA,COLUMNA)
                    if (userInput.Length == 3)
                    {
                        if (userInput[1] == ',' && Char.IsNumber(userInput, 0) && Char.IsNumber(userInput, 2))
                        {
                            // Process the shot on the board
                            tablero.Disparar(new Coordenada(userInput[0].ToString(), userInput[2].ToString()));
                            Console.WriteLine(tablero.ToString());
                        }
                    }
                }
            }
        }

        /// <summary>
        /// Constructor that initializes the game and starts the game loop.
        /// </summary>
        public Game()
        {
            finPartida = false;
            gameLoop();
        }

        /// <summary>
        /// Handles the game-over event when all ships are sunk.
        /// </summary>
        private void cuandoEventoFinDePartida(object sender, EventArgs args)
        {
            finPartida = true;
            Console.WriteLine("GAME ENDED!!");
        }
    }
}
