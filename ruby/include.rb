module Log
	def class_type
		puts "This class is of type: #{self.class}"
	end
end

class TestClass
	include Log
	# ...
end

tc = TestClass.new.class_type
