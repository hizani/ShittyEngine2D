build:
		g++ -std=c++14 -Wfatal-errors \
		-g\
		-no-pie\
		./src/*.cpp \
		-o editor.exe \
		-I/usr/local/lib/wx/include/gtk3-unicode-3.1 -I/usr/local/include/wx-3.1 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__ -pthread\
		-L/usr/local/lib -pthread   -lwx_gtk3u_xrc-3.1 -lwx_gtk3u_html-3.1 -lwx_gtk3u_qa-3.1 -lwx_gtk3u_core-3.1 -lwx_baseu_xml-3.1 -lwx_baseu_net-3.1 -lwx_baseu-3.1
clean:
		rm ./editor.exe;
run:
		./editor.exe;