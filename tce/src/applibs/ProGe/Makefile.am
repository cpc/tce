noinst_LTLIBRARIES = libproge.la
libproge_la_SOURCES = Netlist.cc NetlistBlock.cc NetlistPort.cc \
NetlistGenerator.cc PortConnectionProperty.cc ICDecoderGeneratorPlugin.cc \
NetlistWriter.cc VerilogNetlistWriter.cc VHDLNetlistWriter.cc ProGeUI.cc ProcessorGenerator.cc \
BlockSourceCopier.cc ProGeScriptGenerator.cc ProGeTestBenchGenerator.cc \
VirtualNetlistBlock.cc HDLTemplateInstantiator.cc

SRC_ROOT_DIR = $(top_srcdir)/src
BASE_DIR = ${SRC_ROOT_DIR}/base
APPLIBS_DIR = ${SRC_ROOT_DIR}/applibs

MACH_DIR = ${BASE_DIR}/mach
BEM_DIR = ${BASE_DIR}/bem
IDF_DIR = ${BASE_DIR}/idf
HDB_DIR = ${APPLIBS_DIR}/hdb
ESTIMATOR_DIR = $(srcdir)/../Estimator
BEM_APPLIBS_DIR = ${APPLIBS_DIR}/bem
MACH_APPLIBS_DIR = ${APPLIBS_DIR}/mach
IDF_APPLIBS_DIR = ${APPLIBS_DIR}/idf
TOOLS_DIR = ${SRC_ROOT_DIR}/tools
PLATFORM_DIR=${APPLIBS_DIR}/PlatformIntegrator

AM_CPPFLAGS = -I${TOOLS_DIR} -I${MACH_DIR} -I${BEM_DIR} -I${ESTIMATOR_DIR} \
-I${IDF_DIR} -I${HDB_DIR} -I${BEM_APPLIBS_DIR} -I${MACH_APPLIBS_DIR} \
-I${IDF_APPLIBS_DIR} -I${PLATFORM_DIR}

dist-hook:
	rm -rf $(distdir)/CVS $(distdir)/.deps $(distdir)/Makefile

MAINTAINERCLEANFILES = *~ *.gcov *.bbg *.bb *.da




## headers start
libproge_la_SOURCES += \
	ProGeUI.hh VerilogNetlistWriter.hh \
	HDLTemplateInstantiator.hh NetlistGenerator.hh \
	BlockSourceCopier.hh NetlistBlock.hh \
	NetlistPort.hh VHDLNetlistWriter.hh \
	ICDecoderGeneratorPlugin.hh ProcessorGenerator.hh \
	PortConnectionProperty.hh Netlist.hh \
	ProGeTestBenchGenerator.hh ProGeTypes.hh \
	VirtualNetlistBlock.hh NetlistWriter.hh \
	ProGeScriptGenerator.hh ProGeScriptGenerator.icc 
## headers end
