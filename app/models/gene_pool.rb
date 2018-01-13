class GenePool

  def initialize(city_arr, max_genes, num_kids)
    @distances = {}
    @num_cities = city_arr.length
    @max_genes = max_genes
    @gene_arr = []
    @num_kids = num_kids

    (0...@num_cities).each do |i|
      first_city = city_arr[i]
      @distances[i] = {}
      (0...@num_cities).each do |j|
        second_city = city_arr[j]
        x_sqr = (first_city[0] - second_city[0]).abs2
        y_sqr = (first_city[1] - second_city[1]).abs2
        @distances[i][j] = Math.sqrt(x_sqr + y_sqr)
      end
    end

    Gene.set_cities(@num_cities)
    Gene.set_dists(@distances)

    @gene_arr << Gene.new((0...@num_cities).to_a)
  end

  def one_generation
    new_holder = @gene_arr.dup
    @gene_arr.each do |gene|
      @num_kids.times do
        new_holder << gene.shuffle_child
        new_holder << gene.move_child(true)
        new_holder << gene.move_child(false)
      end
    end
    new_holder.sort! { |a, b| a.get_time - b.get_time }
    new_holder = thin_new_holder
    num_to_copy = [@max_genes, new_holder.length].min
    @gene_arr = new_holder[0...num_to_copy]

  end

  def report_best
    @gene_arr[0].report
  end

  # def num_genes
  #   p "num_genes #{@gene_arr.length}"
  #   @gene_arr.length
  # end
  #
  # def uniform?
  #   # first_time = @gene_arr[0].get_time
  #   # second_time = @gene_arr[-1].get_time
  #   # p "first: #{first_time}, second: #{second_time}"
  #   # first_time == second_time
  #   @gene_arr[0].get_time == @gene_arr[-1].get_time
  # end
  def thin(dirty_arr)
    cleaned_arrs = dirty_arr.map(&:raw_order).uniq
    answer = []
    cleaned_arrs.each do |arr|
      answer << Gene.new(arr)
    end
    answer
  end
end
