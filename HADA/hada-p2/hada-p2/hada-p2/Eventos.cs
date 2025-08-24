using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Hada
{
    /// <summary>
    /// Event arguments for when a ship is hit.
    /// Contains the name of the ship and the impact coordinates.
    /// </summary>
    internal class TocadoArgs
    {
        private string _nombre;
        private Coordenada _coordenadaImpacto;

        /// <summary>
        /// Name of the hit ship.
        /// </summary>
        public string Nombre { get { return _nombre; } set { _nombre = value; } }

        /// <summary>
        /// Coordinates where the ship was hit.
        /// </summary>
        public Coordenada CoordenadaImpacto { get { return _coordenadaImpacto; } set { _coordenadaImpacto = value; } }

        /// <summary>
        /// Constructor initializing the ship name and impact coordinates.
        /// </summary>
        public TocadoArgs(string nombre, Coordenada coordenadaImpacto)
        {
            Nombre = nombre;
            CoordenadaImpacto = coordenadaImpacto;
        }
    }

    /// <summary>
    /// Event arguments for when a ship is sunk.
    /// Contains only the name of the sunk ship.
    /// </summary>
    internal class HundidoArgs
    {
        private string _nombre;

        /// <summary>
        /// Name of the sunk ship.
        /// </summary>
        public string Nombre { get; set; }

        /// <summary>
        /// Constructor initializing the ship name.
        /// </summary>
        public HundidoArgs(string nombre)
        {
            _nombre = nombre;
        }
    }
}
