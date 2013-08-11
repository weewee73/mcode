Gem::Specification.new do |s|
	s.name			= 'hola'
	s.version		= '0.0.0'
	s.executables	<< 'hola'
	s.date			= '2013-07-05'
	s.summary		= "Hola!"
	s.description	= "A simple hello world gem"
	s.authors		= "flyfire"
	s.email			= "zero.flyfire@gmail.com"
	s.files			= ["lib/hola.rb"]
	s.files			+= ["lib/hola/translator.rb"]
	s.test_files	= ['test/test_hola.rb']
	s.homepage		= 'http://rubygems.org/gems/hola'
end
