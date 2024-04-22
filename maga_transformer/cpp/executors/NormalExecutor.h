#pragma once

#include "maga_transformer/cpp/deprecated/ParallelModelWrapper.h"
#include "maga_transformer/cpp/dataclass/MagaInitParameter.h"
#include "maga_transformer/cpp/dataclass/MergedQuery.h"
#include "maga_transformer/cpp/executors/Executor.h"
#include <memory>
namespace rtp_llm {

class NormalExecutor: public Executor {
public:
    explicit NormalExecutor(const MagaInitParams&                                                   params,
                            const std::vector<std::unordered_map<std::string, ft::ConstBufferPtr>>& layer_weights,
                            const std::unordered_map<std::string, ft::ConstBufferPtr>&              weights);
    absl::Status process(const std::list<GenerateStreamPtr>& streams) override;
    void addLoRA(const int64_t                                                   lora_id,
                 const std::vector<std::unordered_map<std::string, ft::ConstBufferPtr>>& lora_a_weights,
                 const std::vector<std::unordered_map<std::string, ft::ConstBufferPtr>>& lora_b_weights) override;
    void removeLoRA(const int64_t lora_id) override;

private:
    // TODO: remove this
    ModelRequest generateOldModelRequest(GptModelInputs& model_input);

private:
    std::unique_ptr<ParallelModelWrapper> model_wrapper_;
};

}  // namespace rtp_llm
