class Gene
  @@num_cities = 0
  @@rand_gen = Random.new
  @@distances = nil

  def self.set_cities(num)
    @@num_cities = num
  end

  def self.set_dists(dists)
    @@distances = dists
  end

  def time_calc
    # p "time_calc test"
    # p "num_cities: #{@@num_cities}"
    # p "city_order: #{@city_order}"
    total = 0
    (0..(@@num_cities - 2)).each do |i|
      total += @@distances[@city_order[i]][@city_order[i + 1]]
    end
    total + @@distances[@city_order[-1]][@city_order[0]]
  end

  def rander
    @@rand_gen.rand(@@num_cities)
  end

  def get_time
    @time
  end

  def initialize(city_order)
    @city_order = city_order
    @time = time_calc
  end

  def shuffle_child
    first = rander
    second = rander
    # p "shuffle_child #{first} #{second}"

    lower = [first, second].min
    upper = [first, second].max

    first_arr = @city_order[0...lower] || []
    second_arr = @city_order[lower..upper]
    third_arr = @city_order[(upper + 1)..-1] || []
    if first < second
      base_arr = first_arr.concat(second_arr.shuffle).concat(third_arr)
    else
      base_arr = third_arr.concat(first_arr).shuffle.concat(second_arr)
    end
    Gene.new(base_arr)
  end

  def move_child(flip)
    adjusted_arr = @city_order.rotate(rander)
    a = rander
    b = rander

    lower = [a, b].min
    upper = [a, b].max
    first_arr = adjusted_arr[0...lower] || []
    second_arr = flip ? adjusted_arr[upper..-1].reverse : adjusted_arr[upper..-1]
    third_arr = adjusted_arr[lower...upper] || []
    full_arr = first_arr.concat(second_arr).concat(third_arr)
    Gene.new(full_arr)
  end

  def report
    # @city_order.join(', ')
    @city_order.dup
  end
end
