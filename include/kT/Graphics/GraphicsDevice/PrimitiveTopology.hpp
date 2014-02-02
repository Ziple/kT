#ifndef __KTPRIMITIVETOPOLOGY_HPP__
#define __KTPRIMITIVETOPOLOGY_HPP__

namespace kT
{
	namespace PrimitiveTopology
	{
		enum Topology
		{
			PointList                    = 1,
			LineList                     = 2,
			LineStrip                    = 3,
			TriangleList                 = 4,
			TriangleStrip                = 5,
			LineListAdj                 = 10,
			LineStripAdj                = 11,
			TriangleListAdj             = 12,
			TriangleStripAdj            = 13
		};
	}
}

#endif /* __KTPRIMITIVETOPOLOGY_HPP__ */