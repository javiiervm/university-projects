using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    /// <summary>
    /// Represents the game board for "Sink the Fleet".
    /// Contains the fired, hit coordinates, and ships in play.
    /// </summary>
    internal class Tablero
    {
        // ====== PUBLIC PROPERTIES WITH BACKUP FIELD ======

        private int tamTablero;

        /// <summary>
        /// Board size (minimum 4, maximum 9).
        /// </summary>
        public int TamTablero
        {
            get => tamTablero;
            private set
            {
                if (value < 4 || value > 9)
                    throw new ArgumentException("The board size must be between 4 and 9.");
                tamTablero = value;
            }
        }

        // ====== PRIVATE PROPERTIES ======

        /// <summary>
        /// List of fired coordinates (all are saved, even if repeated).
        /// </summary>
        private List<Coordenada> coordenadasDisparadas;

        /// <summary>
        /// List of hit coordinates (no repetitions).
        /// </summary>
        private List<Coordenada> coordenadasTocadas;

        /// <summary>
        /// List of active ships on the board.
        /// </summary>
        private List<Barco> barcos;

        /// <summary>
        /// List of eliminated ships (no repetitions).
        /// </summary>
        private List<Barco> barcosEliminados;

        /// <summary>
        /// Dictionary storing the state of each board square.
        /// The squares are coordinates and the values can be:
        /// - "AGUA" → No ship.
        /// - "SHIP_NAME" → Square occupied by a ship.
        /// - "SHIP_NAME_T" → Square occupied by a hit ship.
        /// </summary>
        private Dictionary<Coordenada, string> casillasTablero;

        // ====== CONSTRUCTOR ======

        /// <summary>
        /// Board constructor. Initializes its properties and registers events.
        /// </summary>
        public Tablero(int tamTablero, List<Barco> barcos)
        {
            this.TamTablero = tamTablero;
            if (barcos == null) throw new ArgumentNullException(nameof(barcos)); else this.barcos = barcos;

            coordenadasDisparadas = new List<Coordenada>();
            coordenadasTocadas = new List<Coordenada>();
            barcosEliminados = new List<Barco>();
            casillasTablero = new Dictionary<Coordenada, string>();

            // Initialize the events of each ship
            foreach (Barco barco in barcos)
            {
                barco.eventoTocado += cuandoEventoTocado;
                barco.eventoHundido += cuandoEventoHundido;
            }


            // Initialize the state of the squares
            inicializaCasillasTablero();
        }

        // ====== PRIVATE METHODS ======

        /// <summary>
        /// Initializes the board squares with "AGUA" or the name of the ship if there is one in the position.
        /// </summary>
        private void inicializaCasillasTablero()
        {
            for (int fila = 0; fila < TamTablero; fila++)
            {
                for (int columna = 0; columna < TamTablero; columna++)
                {
                    Coordenada coord = new Coordenada(fila, columna);
                    casillasTablero[coord] = "AGUA";
                }
            }

            // Place the ships on the board
            foreach (Barco barco in barcos)
            {
                foreach (var coord in barco.CoordenadasBarco.Keys)
                {
                    casillasTablero[coord] = barco.Name;
                }
            }
        }

        // ====== PUBLIC METHODS ======

        /// <summary>
        /// Registers a shot and checks if it hit a ship.
        /// </summary>
        public void Disparar(Coordenada c)
        {
            // Check if the coordinate is within the board
            if (c.Fila >= TamTablero || c.Columna >= TamTablero)
            {
                Console.WriteLine($"The coordinate {c.ToString()} is outside the dimensions of the board");
                return;
            }

            // Add the fired coordinate to the list
            coordenadasDisparadas.Add(c);

            // Check if the shot hits a ship
            foreach (Barco barco in barcos)
            {
                if (barco.CoordenadasBarco.ContainsKey(c))
                {
                    barco.Disparo(c);   // The ship handles the hit
                    if (!coordenadasTocadas.Contains(c))
                        coordenadasTocadas.Add(c);
                    return;
                }
            }
        }

        /// <summary>
        /// Generates a string representing the visual state of the board.
        /// </summary>
        public string DibujarTablero()
        {
            // String to return
            string tablero = "CASILLAS TABLERO\n-------\n";

            for (int fila = 0; fila < TamTablero; fila++)
            {
                for (int columna = 0; columna < TamTablero; columna++)
                {
                    // Add the information of each board coordinate
                    Coordenada coord = new Coordenada(fila, columna);
                    tablero += $"[{casillasTablero[coord]}]";
                }
                // When changing rows, add a newline
                tablero += $"\n";
            }

            return tablero;
        }

        /// <summary>
        /// Returns information about the current state of the board.
        /// </summary>
        public override string ToString()
        {
            // String to return
            string info = "";

            // Add information of each ship in the list
            foreach (Barco barco in barcos)
            {
                info += barco.ToString();
                info += "\n";
            }
            info += "\n";

            // List fired coordinates
            info += "Coordenadas disparadas: ";
            foreach (Coordenada coor in coordenadasDisparadas)
            {
                info += coor.ToString();
                info += " ";
            }
            info += "\n";

            // List hit coordinates
            info += "Coordenadas tocadas: ";
            foreach (Coordenada coor in coordenadasTocadas)
            {
                info += coor.ToString();
                info += " ";
            }
            info += "\n\n\n\n";

            // List board squares
            info += DibujarTablero();
            info += "\n\n";

            return info;
        }

        // ====== EVENT HANDLING ======

        /// <summary>
        /// Handles the ship hit event and updates the board state.
        /// </summary>
        private void cuandoEventoTocado(object sender, TocadoArgs args)
        {
            casillasTablero[args.CoordenadaImpacto] = args.Nombre;
            coordenadasTocadas.Add(args.CoordenadaImpacto);
            Console.WriteLine($"TABLERO: Barco {args.Nombre} tocado en\nCoordenada: {args.CoordenadaImpacto.ToString()}");
        }


        /// <summary>
        /// Handles the sunk ship event and checks if the game is over.
        /// </summary>
        private void cuandoEventoHundido(object sender, HundidoArgs args)
        {
            bool todosHundidos = true;
            Console.WriteLine($"TABLERO: Barco {args.Nombre} hundido!!\n");
            foreach (Barco barco in barcos)
            {
                if (!barco.hundido())
                {
                    todosHundidos = false;
                    break;
                }
            }
            if (todosHundidos) eventoFinPartida(this, EventArgs.Empty);
        }


        // ====== PUBLIC EVENTS ======

        /// <summary>
        /// Triggered when all ships have been sunk.
        /// </summary>
        public event EventHandler<EventArgs> eventoFinPartida;
    }
}