# encoding: utf-8
class Hola::Translator
	def initialize(language)
		@language = language
	end

	def hi
		case @language
		when :chinese
			"您好"
		when :spanish
			"hola mundo"
		when :english
			"hello world"
		else
			"Hello world! I'm flyfire."
		end
	end
end
