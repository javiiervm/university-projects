using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    /// <summary>
    /// Represents a Ship for the game
    /// </summary>
    internal class Barco
    {
        // Private field containing the coordinates and tags for each coordinate (read only)
        private readonly Dictionary<Coordenada, String> _coordenadasBarco;

        // Private field containing the ship's name. Must be unique (constraint controled from Game class)
        private string _name;

        // Private field containing the ship's damage.
        private int _numDanyos;

        public event EventHandler<TocadoArgs> eventoTocado;

        public event EventHandler<HundidoArgs> eventoHundido;

        /// <summary>
        /// Allows the client code to read the contnents of the field _coordenadasBarco
        /// </summary>
        public Dictionary<Coordenada, String> CoordenadasBarco
        {
            get
            {
                return _coordenadasBarco;
            }

            private set
            {
                // No mention of what to put inside here
                // Ask in class
            }
        }

        // No mention of what this property's setters and getters should do
        public string Name { get { return _name; } set { _name = value; } }

        // Public property that takes care of the amount of damage the ship has taken
        public int NumDanyos { get { return _numDanyos; } set { _numDanyos = value; } }

        /// <summary>
        /// Class constructor
        /// </summary>
        /// <param name="nombre">Name of the ship</param>
        /// <param name="longitud">Length of the ship in the indicated orientation</param>
        /// <param name="orientacion">Orientation of the ship, must be 'h' or 'v'</param>
        /// <param name="coordenadaInicio">Initial coordinate to calculate all other coordinates from the ship</param>
        /// <exception cref="ArgumentException">Thrown if the orientation is invalid</exception>
        public Barco(string nombre, int longitud, char orientacion, Coordenada coordenadaInicio)
        {
            _name = nombre;
            _numDanyos = 0;
            _coordenadasBarco = new Dictionary<Coordenada, string>();

            if (orientacion == 'h')     // Horizontal position (spans across columns)
            {
                for (int i = 0; i < longitud; i++)
                {
                    CoordenadasBarco.Add(
                        new Coordenada(coordenadaInicio.Fila, coordenadaInicio.Columna + i), 
                        nombre
                    );
                }
            }
            else if (orientacion == 'v')   // Vertical position (spans across rows)
            {
                for (int i = 0; i < longitud; i++)
                {
                    CoordenadasBarco.Add(
                        new Coordenada(coordenadaInicio.Fila + i, coordenadaInicio.Columna),
                        nombre
                    );
                }
            }
            else
            {
                throw new ArgumentException("Invalid orientation received");
            }
        }

        /// <summary>
        /// Shoots a certain coordinate
        /// </summary>
        /// <param name="c">Coordinate to shoot</param>
        public void Disparo(Coordenada c)
        {
            bool hasCoord = false;

            if (CoordenadasBarco.ContainsKey(c))
            {
                if (!CoordenadasBarco[c].Contains("_T"))
                {
                    CoordenadasBarco[c] += "_T";
                }
                

                if (eventoTocado != null)
                {
                    eventoTocado(this, new TocadoArgs(CoordenadasBarco[c], c));
                }

                _numDanyos++;

                if (hundido())
                {
                    if (eventoHundido != null)
                    {
                        eventoHundido(this, new HundidoArgs(_name));
                    }
                }
            }
        }

        /// <summary>
        /// Method that checks whether the ship sunk or not
        /// </summary>
        /// <returns>True if the ship sunk, false otherwise</returns>
        public bool hundido()
        {
            foreach(KeyValuePair<Coordenada, string> celda in CoordenadasBarco)
            {
                if (celda.Value == _name)
                {
                    return false;
                }
            }
            // If the program reaches this part, it means
            // that all the ship's cells were touched so it sank
            return true;
        }

        /// <summary>
        /// Returns a string representation of the ship's info in the specified format
        /// </summary>
        /// <returns>String representation</returns>
        public override string ToString()
        {
            string tempString = $"[{Name}] - DAÑOS: [{NumDanyos}] - HUNDIDO: [{hundido()}] - COORDENADAS:";

            foreach (KeyValuePair<Coordenada, string> celda in CoordenadasBarco)
            {
                tempString += $" [{celda.Key} :{celda.Value}]";
            }

            return tempString;
        }
    }
}
