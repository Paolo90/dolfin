"This demo illustrates basic plotting."

# Copyright (C) 2013 Jan Blechta 
#
# This file is part of DOLFIN.
#
# DOLFIN is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# DOLFIN is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with DOLFIN. If not, see <http://www.gnu.org/licenses/>.
#
# First added:  2013-11-19
# Last changed:

from dolfin import *

# Read and show mesh
mesh = Mesh("../dolfin_fine.xml.gz")
#plot(mesh)

# Print minimal and maximal radius ratio
qmin, qmax = MeshQuality.radius_ratio_min_max(mesh)
print 'Minimal radius ratio:', qmin
print 'Maximal radius ratio:', qmax

# Show histogram using matplotlib
hist = MeshQuality.radius_ratio_matplolib_histogram(mesh)
hist = hist.replace('pylab.show()', 'pylab.show(block=False)')
#hist = hist.replace('pylab.show()', '')
print hist
exec(hist)

# Show mesh
plot(mesh)
interactive()
