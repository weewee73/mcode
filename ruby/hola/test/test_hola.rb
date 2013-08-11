# encoding: utf-8
require 'test/unit'
require 'hola'

class HolaTest < Test::Unit::TestCase
	def test_english_hello
		assert_equal "hello world", Hola.hi("english")
	end

	def test_spanlish_hello
		assert_equal "hola mundo", Hola.hi("spanish")
	end

	def test_chinese_hello
		assert_equal "您好", Hola.hi("chinese")
	end

	def test_any_hello
		assert_equal "Hello World! I'm flyfire.", Hola.hi("ruby")
	end
end
