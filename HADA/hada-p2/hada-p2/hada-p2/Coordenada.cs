using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    /// <summary>
    /// Represents a coordinate on a board with row and column values between 0 and 9.
    /// </summary>
    internal class Coordenada
    {
        // Private fields storing the row and column.
        private int fila;
        private int columna;

        /// <summary>
        /// Public property to access the row.
        /// Only allows assignments within the range [0,9].
        /// </summary>
        public int Fila
        {
            get => fila;
            private set
            {
                if (value < 0 || value > 9)
                    throw new ArgumentException("Only values between 0 and 9 are allowed!");
                fila = value;
            }
        }

        /// <summary>
        /// Public property to access the column.
        /// Only allows assignments within the range [0,9].
        /// </summary>
        public int Columna
        {
            get => columna;
            private set
            {
                if (value < 0 || value > 9)
                    throw new ArgumentException("Only values between 0 and 9 are allowed!");
                columna = value;
            }
        }

        /// <summary>
        /// Default constructor. Initializes the coordinate to (0,0).
        /// </summary>
        public Coordenada()
        {
            this.Fila = 0;
            this.Columna = 0;
        }

        /// <summary>
        /// Constructor that receives a row and a column of type int.
        /// Throws an exception if the values are out of the allowed range [0,9].
        /// </summary>
        public Coordenada(int Fila, int Columna)
        {
            this.Fila = Fila;
            this.Columna = Columna;
        }

        /// <summary>
        /// Constructor that receives a row and a column as strings.
        /// Throws an exception if the strings are empty or not convertible to int.
        /// </summary>
        public Coordenada(string Fila, string Columna)
        {
            if (string.IsNullOrEmpty(Fila) || string.IsNullOrEmpty(Columna))
                throw new ArgumentException("Strings can't be empty!");

            this.Fila = int.Parse(Fila);  // Converts the row from string to int
            this.Columna = int.Parse(Columna);  // Converts the column from string to int
        }

        /// <summary>
        /// Copy constructor. Creates a new Coordenada based on an existing one.
        /// </summary>
        public Coordenada(Coordenada other)
        {
            this.Fila = other.Fila;
            this.Columna = other.Columna;
        }

        /// <summary>
        /// Returns the text representation of the coordinate in format (Row,Column).
        /// </summary>
        public override string ToString()
        {
            return $"({Fila},{Columna})";
        }

        /// <summary>
        /// Returns a unique hash code for the coordinate.
        /// Uses XOR between the row and column hashes to generate a unique identifier.
        /// </summary>
        public override int GetHashCode()
        {
            return this.Fila.GetHashCode() ^ this.Columna.GetHashCode();
        }

        /// <summary>
        /// Compares this coordinate with another object to determine if they are equal.
        /// </summary>
        /// <param name="obj">Object to compare</param>
        /// <returns>true if it is a coordinate with the same row and column, false otherwise.</returns>
        public override bool Equals(object obj)
        {
            return obj is Coordenada other && this.Fila == other.Fila && this.Columna == other.Columna;
        }

        /// <summary>
        /// Compares this coordinate with another of the same type to determine if they are equal.
        /// </summary>
        /// <param name="other">Another instance of Coordenada</param>
        /// <returns>true if both coordinates have the same row and column, false otherwise.</returns>
        public bool Equals(Coordenada other)
        {
            if (other == null) return false;
            return (this.Fila == other.Fila && this.Columna == other.Columna);
        }
    }
}