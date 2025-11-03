run : bin/animacion_cohete
	./bin/animacion_cohete

bin/animacion_cohete : animacion_cohete.cpp
	@mkdir -p bin
	g++ -o bin/animacion_cohete animacion_cohete.cpp -std=c++17 -lftxui-component -lftxui-dom -lftxui-screen

clean:
	rm -rf bin/animacion_cohete
